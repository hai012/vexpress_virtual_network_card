cmd_/mnt/samba/petalinux/zcu102/work/get_addr/utils.o := gcc -Wp,-MMD,/mnt/samba/petalinux/zcu102/work/get_addr/.utils.o.d  -nostdinc -isystem /usr/lib/gcc/aarch64-linux-gnu/9/include -I/root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include -I./arch/arm64/include/generated -I/root/petalinux/linux-xlnx-xilinx-v2021.1/include -I./include -I/root/petalinux/linux-xlnx-xilinx-v2021.1/arch/arm64/include/uapi -I./arch/arm64/include/generated/uapi -I/root/petalinux/linux-xlnx-xilinx-v2021.1/include/uapi -I./include/generated/uapi -include /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -DCC_USING_PATCHABLE_FUNCTION_ENTRY -DKASAN_SHADOW_SCALE_SHIFT=3 -fmacro-prefix-map=/root/petalinux/linux-xlnx-xilinx-v2021.1/= -D__ASSEMBLY__ -fno-PIE -mabi=lp64 -fno-asynchronous-unwind-tables -fno-unwind-tables -DKASAN_SHADOW_SCALE_SHIFT=3 -Wa,-gdwarf-2  -DMODULE  -c -o /mnt/samba/petalinux/zcu102/work/get_addr/utils.o /mnt/samba/petalinux/zcu102/work/get_addr/utils.S

source_/mnt/samba/petalinux/zcu102/work/get_addr/utils.o := /mnt/samba/petalinux/zcu102/work/get_addr/utils.S

deps_/mnt/samba/petalinux/zcu102/work/get_addr/utils.o := \
  /root/petalinux/linux-xlnx-xilinx-v2021.1/include/linux/kconfig.h \
    $(wildcard include/config/cc/version/text.h) \
    $(wildcard include/config/cpu/big/endian.h) \
    $(wildcard include/config/booger.h) \
    $(wildcard include/config/foo.h) \

/mnt/samba/petalinux/zcu102/work/get_addr/utils.o: $(deps_/mnt/samba/petalinux/zcu102/work/get_addr/utils.o)

$(deps_/mnt/samba/petalinux/zcu102/work/get_addr/utils.o):
