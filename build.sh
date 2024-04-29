#!/bin/bash
. /opt/fslc-framebuffer/3.1/environment-setup-cortexa9t2hf-neon-fslc-linux-gnueabi

if [[ ! -d build ]]; then
mkdir -p build
fi

cd build
rm -rfd *
now=$(date +"%d.%b.%Y_%H:%M")
log="build_log.$now.log"
error="error_log.$now.log"


make clean 
qmake ../IC-12_MVP_Dashboard.pro
make -j4 1>$log 2>$error
#scp IC-12_MVP_Dashboard root@$1:
cd ..
#cd ..
#cd build-IC-12_MVP_Dashboard-Desktop_Qt_5_15_2_GCC_64bit-Debug
#scp /etc/config_data.json root@$1:/etc
#scp IC-12_MVP_Dashboard > log.log root@$1:



