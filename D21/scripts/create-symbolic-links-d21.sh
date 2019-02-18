if [ -z "$1" ];then
	echo "Error. No path supplied..."
	exit -1
fi

#in inc
ln -s /home/penguin/Documents/ASF_MODULES/xdk-asf-3.45.0/sam0/utils/cmsis/samd21/include ${1}/inc
ln -s /home/penguin/Documents/ASF_MODULES/xdk-asf-3.45.0/thirdparty/CMSIS/Include ${1}/inc/cmsis
ln -s /home/penguin/Documents/ASF_MODULES/xdk-asf-3.45.0/sam0/utils/cmsis/samd21/source/system_samd21.h ${1}/inc
#in build
ln -s /home/penguin/Documents/ASF_MODULES/xdk-asf-3.45.0/sam0/utils/linker_scripts/samd21/gcc/samd21j18a_flash.ld ${1}/build


#in src
ln -s /home/penguin/Documents/ASF_MODULES/xdk-asf-3.45.0/sam0/utils/cmsis/samd21/source/gcc/startup_samd21.c ${1}/src
ln -s /home/penguin/Documents/ASF_MODULES/xdk-asf-3.45.0/sam0/utils/cmsis/samd21/source/system_samd21.c ${1}/src

