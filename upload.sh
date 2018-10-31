#!/usr/bin/env bash
#stty -F /dev/ttyACM0 1200
#sleep 2
bossac -e -w -v -b cmake-build-run/llib.bin -p ttyACM0 -U false -R