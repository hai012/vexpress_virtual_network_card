#!/bin/bash

#export ARCH=arm
#export CROSS_COMPILE=/home/haijie.gong/disk/imx6ull_qemu/ToolChain-6.2.1/bin/arm-linux-gnueabihf-
#export CROSS_COMPILE=/home/haijie.gong/tools/gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-
#make -j16 KBUILD_OUTPUT=../out/busybox distclean
#make -j16 KBUILD_OUTPUT=../out/busybox defconfig
#make -j16 KBUILD_OUTPUT=../out/busybox menuconfig
#make -j16 KBUILD_OUTPUT=../out/busybox
make -j16 KBUILD_OUTPUT=../out/busybox install
