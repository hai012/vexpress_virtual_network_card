qemu_src=`pwd`
cd ../out/qemu
#$qemu_src/configure  --target-list="arm-softmmu arm-linux-user" --enable-debug --enable-sdl --enable-tools --disable-curl  --enable-slirp
make -j16
