#!/usr/bin/env bash
#sleep 1
stty -F /dev/ttyACM1 1200
sleep 2
bossac -v -e -w -v -b cmake-build-llib/llib.bin -p ttyACM1 -U false -R
./tools/lpc21isp_197/lpc21isp_hr_linux -termonly /dev/ttyACM1 115200 12000