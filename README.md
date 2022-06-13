# steamdeck-k10temp-driver

This is a standalone/dkms build of the k10temp.ko kernel driver that
contains the additions to recognise the Steam Deck's custom APU.

It's a bit ugly because it requires including a private modified
copy of the AMD northbridge logic that is part of the kernel itself,
and is normally outside the driver.
