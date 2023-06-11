
#export ARCH=arm
#export CROSS_COMPILE=/home/haijie.gong/tools/gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-
make  -j16
cp mynet_driver.ko ~/tmp
