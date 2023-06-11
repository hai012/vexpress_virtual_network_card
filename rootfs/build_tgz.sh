rm -rf rootfs.tgz
mkdir mnt
mount rootfs.ext4 mnt
tar zcf rootfs.tgz mnt
umount mnt
rm -rf mnt
