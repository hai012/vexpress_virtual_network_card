
obj-m := list.o

KERNELDIR=/home/haijie.gong/disk/mynet/linux-6.1.15
all default: modules
install: modules_install
modules modules_install help clean:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) $@
	cp list.ko ~/tmp/
