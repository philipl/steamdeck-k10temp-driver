# normal makefile
KDIR ?= /lib/modules/`uname -r`/build
obj-m := k10temp.o
k10temp-objs := k10temp_main.o internal/amd_nb.o internal/msr.o

modules:

%:
	$(MAKE) -C $(KDIR) M=$$PWD $@
