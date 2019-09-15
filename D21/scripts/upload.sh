#!/bin/bash
set -x
if [ -n "$1" ];then
	echo "Uploading $1..."
else
	echo "No arg supplied!"
	exit -1
fi
ELF=$1
SWPATH=/storage/Shared/Documents/Projects/project_bare_metal/D21
DEBUGPATH=$SWPATH/debug/bin
MAKEPATH=$SWPATH/bin
RED="\033[0;31m"
NC='\033[0m'
BOLD='\e[1m'
BOLDRED='\033[1;31m'
echo "Killing terminal..."

if ps aux | grep openocd | grep -v grep >/dev/null;then
	echo "OpenOCD Running..."
else
	echo "Opening fresh OpenOCD..."
	(cd /home/penguin; openocd >/dev/null 2>&1 &)
fi


if ps aux | grep ./bm_d21_debug | grep -v grep >/dev/null;then
	pid=$(ps aux | grep ./bm_d21_debug | grep -v grep | awk '{print $2}')
	(kill -9 ${pid}; echo "clear; reset" > $BM_D21_DEBUG_PIPE)
	printf "echo -e \"${BOLDRED}Loading new terminal...${NC}\"\n" > $BM_D21_DEBUG_PIPE
	printf "stty -echo\n" > $BM_D21_DEBUG_PIPE
fi


if [ $? -eq 124 ];then
	echo "^Z" >/dev/null
	echo "" >/dev/null
	echo "Failed to connect processor through openocd. Do you have it running?"
	echo "exiting..."
	echo "echo -e \"${BOLDRED}Failed to load terminal. Check dev console${NC}\"" > $BM_D21_DEBUG_PIPE
	echo "echo \"Waiting on connection...\"" > $BM_D21_DEBUG_PIPE
	exit -1
else
	echo "Connected to OpenOCD"
fi

# 	echo "Upload success"
# else
# 	echo "Failed to upload. Is openocd connected?"
# 	exit -1
# fi

echo "Restarting terminal..."
if [ ! -f "${DEBUGPATH}/bm_d21_debug" ];then
	echo "No debug program found..."
else
	dd if=$BM_D21_DEBUG_PIPE iflag=nonblock of=/dev/null >/dev/null 2>&1
	printf "stty echo;" > $BM_D21_DEBUG_PIPE
	printf "clear;" > $BM_D21_DEBUG_PIPE
	printf "echo -e \"${BOLDRED}Terminal open${NC} on ... \";" > $BM_D21_DEBUG_PIPE
	printf "" > $BM_D21_DEBUG_PIPE
	printf "${DEBUGPATH}//bm_d21_debug" > $BM_D21_DEBUG_PIPE
	timeout --foreground 3 arm-none-eabi-gdb -x "../build/flashmcu.gdb" --args $ELF >/dev/null
fi
exit $?
