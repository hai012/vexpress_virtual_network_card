

obj-m := virt_netdev_a.o
obj-m := virt_netdev_b.o
obj-m := virt_netdev_hw.o

KERNELDIR = /root/petalinux/build
all default: modules
install: modules_install
modules modules_install help clean:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) $@
