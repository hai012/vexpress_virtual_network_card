#srcroot=`pwd`
#cd ../out/iperf
#${srcroot}/configure  --host=arm CC="${CROSS_COMPILE}gcc"  CXX="${CROSS_COMPILE}g++"
./configure  --host=arm CC="${CROSS_COMPILE}gcc"  CXX="${CROSS_COMPILE}g++"
make -j16
