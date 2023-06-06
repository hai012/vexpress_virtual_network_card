rm -rf rootfs.ext4
dd if=/dev/zero of=rootfs.ext4 bs=1G count=2
mkfs.ext4 rootfs.ext4
mkdir rootfs
mount rootfs.ext4 rootfs
tar zxf rootfs.tgz
mv mnt/* rootfs/
rm -rf mnt
umount rootfs
