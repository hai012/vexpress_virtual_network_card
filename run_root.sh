#!/bin/bash

#workdir=qemu-system-arm
#workdir=/home/haijie.gong/disk/mynet/qemu/build/qemu-system-arm

#QEMU=qemu-system-arm
QEMU=out/qemu/qemu-system-arm
KERNEL=out/kernel/arch/arm/boot/zImage
SD_IMAGE=rootfs/rootfs.ext4
#SD_IMAGE=rootfs/ubuntu_rootfs.ext4

MACHINE=vexpress-a9
CORES=4
DTB=out/kernel/arch/arm/boot/dts/vexpress-v2p-ca9.dtb

#MACHINE=vexpress-a15
#CORES=2
#DTB=out/kernel/arch/arm/boot/dts/vexpress-v2p-ca15-tc1.dtb

SNAT=`iptables -t nat  -L POSTROUTING|grep "MASQUERADE  all  --  192.168.0.0/24       anywhere"`
if [ -z "$SNAT" ]
then
	iptables -t nat -I POSTROUTING -s 192.168.0.0/24 -o ens33 -j MASQUERADE
	iptables -t nat -I POSTROUTING -s 192.168.0.0/24 -o ens3 -j MASQUERADE
fi
iptables -t filter -P FORWARD ACCEPT


ulimit -c unlimited
#$QEMU -M $MACHINE  -accel tcg,thread=multi -cpu cortex-a9  -smp $CORES  -m 1G -kernel $KERNEL -dtb $DTB -nographic -serial mon:stdio   -append 'console=ttyAMA0 rootfstype=ext4 root=/dev/mmcblk0  rw rootwait init=/sbin/init  loglevel=8'  -drive  file=${SD_IMAGE},format=raw,id=mysdcard -device sd-card,drive=mysdcard  -nic user
$QEMU -M $MACHINE  -accel tcg,thread=multi -cpu cortex-a9  -smp $CORES  -m 1G -kernel $KERNEL -dtb $DTB -nographic -serial mon:stdio   -append 'console=ttyAMA0 rootfstype=ext4 root=/dev/mmcblk0  rw rootwait init=/sbin/init  loglevel=8'  -sd $SD_IMAGE  -nic user
