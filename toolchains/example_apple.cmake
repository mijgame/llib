cmake_minimum_required(VERSION 3.11)

set(OBJCOPY "/opt/arm-none-eabi/bin/arm-none-eabi-objcopy")
set(CMAKE_C_COMPILER "/opt/arm-none-eabi/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "/opt/arm-none-eabi/bin/arm-none-eabi-g++")
set(TERMINAL "${CMAKE_CURRENT_SOURCE_DIR}/tools/lpc21isp_197/lpc21isp_hr_linux")
set(BOSSAC "bossac")
set(SERIAL_PORT /dev/ttyACM0)