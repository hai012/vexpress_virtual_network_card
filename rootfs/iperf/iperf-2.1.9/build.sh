#!/bin/bash

srcroot=`pwd`
rm -rf ../../../out/iperf_arm 2>/dev/null
mkdir ../../../out/iperf_arm
cd ../../../out/iperf_arm
${srcroot}/configure  --host=arm CC="${CROSS_COMPILE}gcc"  CXX="${CROSS_COMPILE}g++"
make -j16 

cd ${srcroot}
rm -rf ../../../out/iperf_x86_64 2>/dev/null
mkdir ../../../out/iperf_x86_64
cd ../../../out/iperf_x86_64
${srcroot}/configure
make -j16 
