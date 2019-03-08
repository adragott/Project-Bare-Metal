set pagination off
set logging file ../log/resetmculog.txt
set logging on
info breakpoints
set tcp connect-timeout 3
set remotetimeout 3
target extended-remote localhost:3333 arg1
load
monitor reset
set logging off
quit
