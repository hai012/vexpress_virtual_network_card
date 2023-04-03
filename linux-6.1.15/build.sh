#!/bin/bash



#export ARCH=arm
#export CROSS_COMPILE=/home/haijie.gong/tools/gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-
#export KBUILD_OUTPUT=../out/kernel




#make -j16 distclean
#make -j16 imx_v6_v7_defconfig
#make -j16 multi_v7_defconfig
#make -j16 vexpress_defconfig
#make -j16 menuconfig
#make -j16 savedefconfig

#make -j16 defconfig


#make -j16 zImage && cp arch/arm/boot/zImage /home/haijie.gong/imx_qemu_run/imx6q-system-image/
#make -j16 imx6q-sabrelite.dtb && cp  arch/arm/boot/dts/100ask_imx6ull_qemu.dtb /home/haijie.gong/imx_qemu_run/imx6q-system-image/

cp board_defconfig ../out/kernel/.config
#cp ../out/kernel/.config board_defconfig

make -j16 KBUILD_OUTPUT=../out/kernel zImage
make -j16 KBUILD_OUTPUT=../out/kernel modules
make -j16 KBUILD_OUTPUT=../out/kernel vexpress-v2p-ca9.dtb
make -j16 KBUILD_OUTPUT=../out/kernel vexpress-v2p-ca15-tc1.dtb


echo "
make -j16  KBUILD_OUTPUT=../out/kernel menuconfig
make -j16  KBUILD_OUTPUT=../out/kernel zImage
make -j16  KBUILD_OUTPUT=../out/kernel modules
make -j16  KBUILD_OUTPUT=../out/kernel vexpress-v2p-ca9.dtb
make -j16  KBUILD_OUTPUT=../out/kernel vexpress-v2p-ca15-tc1.dtb
"
