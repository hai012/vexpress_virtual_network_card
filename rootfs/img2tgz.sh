rm -rf rootfs.tgz mnt 2>/dev/null
mkdir mnt
mount rootfs.ext4 mnt
tar zcf rootfs.tgz mnt
umount mnt
rm -rf mnt
