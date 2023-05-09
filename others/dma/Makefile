CFLAGS += -g 
obj-m := dma_copy_test.o
KERNELDIR = /root/petalinux/build
all default: modules
install: modules_install
modules modules_install help clean:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) $@
