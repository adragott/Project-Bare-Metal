if [ -z "$1" ];then
	echo "Error. No path supplied..."
	exit -1
fi

rm -rf $1/inc/include
rm -rf $1/inc/cmsis
rm -rf $1/inc/system_samd21.h

rm -rf $1/build/samd21j18a_flash.ld

rm -rf $1/src/startup_samd21.c
rm -rf $1/src/system_samd21.c
#in inc
ln -s /home/penguin/Documents/ASF_MODULES/xdk-asf-3.46.0/sam0/utils/cmsis/samd21/include ${1}/inc
ln -s /home/penguin/Documents/ASF_MODULES/xdk-asf-3.46.0/thirdparty/CMSIS/Include ${1}/inc/cmsis
ln -s /home/penguin/Documents/ASF_MODULES/xdk-asf-3.46.0/sam0/utils/cmsis/samd21/source/system_samd21.h ${1}/inc
#in build
ln -s /home/penguin/Documents/ASF_MODULES/xdk-asf-3.46.0/sam0/utils/linker_scripts/samd21/gcc/samd21j18a_flash.ld ${1}/build


#in src
ln -s /home/penguin/Documents/ASF_MODULES/xdk-asf-3.46.0/sam0/utils/cmsis/samd21/source/gcc/startup_samd21.c ${1}/src
ln -s /home/penguin/Documents/ASF_MODULES/xdk-asf-3.46.0/sam0/utils/cmsis/samd21/source/system_samd21.c ${1}/src
