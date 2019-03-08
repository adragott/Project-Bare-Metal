#!/bin/bash
clear
stty -echo
while true
do
	eval $(cat ${BM_D21_DEBUG_PIPE})
done
