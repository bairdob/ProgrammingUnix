ifneq ($(KERNELRELEASE),)
    obj-m := pci_skel.o

CONFIG_MODULE_SIG=n
CONFIG_MODULE_SIG_ALL=n

else
    KERNEL_DIR ?= /lib/modules/$(shell uname -r)/build
    PWD := $(shell pwd)

all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD)

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions modules.order Module.symvers *.mod notes


endif
