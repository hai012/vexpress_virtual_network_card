CFLAGS += -g -w
obj-m := get_info.o
get_info-y += get_addr.o
get_info-y += utils.o
KERNELDIR = /root/petalinux/build


all default: modules
install: modules_install
modules modules_install help clean:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) $@
