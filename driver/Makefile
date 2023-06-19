
obj-m := mynet_driver.o
mynet_driver-objs := mynet.o ring.o irq.o


KERNELDIR=$(shell pwd)/../out/kernel
all default: modules
install: modules_install
modules modules_install help clean:
	#$(MAKE) -C $(KERNELDIR) M=$(shell pwd) KCFLAGS=-g V=1 $@
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) V=1 $@
