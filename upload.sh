#!/usr/bin/env bash
#stty -F /dev/ttyACM0 1200
#sleep 2
bossac -e -w -v -b cmake-build-llib/llib.bin -p ttyACM0 -U false -R
./tools/lpc21isp_197/lpc21isp_hr_linux -termonly /dev/ttyACM0 115200 12000