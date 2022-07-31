// SPDX-License-Identifier: GPL-2.0
#include <asm/msr.h>

/**
 * Read an MSR with error handling
 *
 * @msr: MSR to read
 * @m: value to read into
 *
 * It returns read data only on success, otherwise it doesn't change the output
 * argument @m.
 *
 */
static int msr_read(u32 msr, struct msr *m)
{
	int err;
	u64 val;

	err = rdmsrl_safe(msr, &val);
	if (!err)
		m->q = val;

	return err;
}

/**
 * Write an MSR with error handling
 *
 * @msr: MSR to write
 * @m: value to write
 */
static int msr_write(u32 msr, struct msr *m)
{
	return wrmsrl_safe(msr, m->q);
}

static inline int __flip_bit(u32 msr, u8 bit, bool set)
{
	struct msr m, m1;
	int err = -EINVAL;

	if (bit > 63)
		return err;

	err = msr_read(msr, &m);
	if (err)
		return err;

	m1 = m;
	if (set)
		m1.q |=  BIT_64(bit);
	else
		m1.q &= ~BIT_64(bit);

	if (m1.q == m.q)
		return 0;

	err = msr_write(msr, &m1);
	if (err)
		return err;

	return 1;
}

/**
 * Set @bit in a MSR @msr.
 *
 * Retval:
 * < 0: An error was encountered.
 * = 0: Bit was already set.
 * > 0: Hardware accepted the MSR write.
 */
int msr_set_bit(u32 msr, u8 bit)
{
	return __flip_bit(msr, bit, true);
}
