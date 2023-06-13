rm -rf rootfs.ext4 mnt rootfs 2>/dev/null
dd if=/dev/zero of=rootfs.ext4 bs=1G count=2
mkfs.ext4 rootfs.ext4
mkdir rootfs
mount rootfs.ext4 rootfs
tar zxf rootfs.tgz 
mv mnt/* rootfs/
umount rootfs
rm -rf mnt rootfs
