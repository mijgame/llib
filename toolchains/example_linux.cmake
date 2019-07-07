cmake_minimum_required(VERSION 3.11)

# compiler settings
set(CMAKE_C_COMPILER "$ENV{HOME}/opt/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "$ENV{HOME}/opt/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi-g++")

# arm-eabi
set(ARM_EABI_OBJCOPY "$ENV{HOME}/opt/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi-objcopy")
set(ARM_EABI_OBJDUMP "$ENV{HOME}/opt/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi-objdump")
set(ARM_EABI_SIZE "$ENV{HOME}/opt/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi-size")

# other settings
set(TERMINAL "${CMAKE_CURRENT_SOURCE_DIR}/tools/lpc21isp_197/lpc21isp_hr_linux")
set(BOSSAC "bossac")
set(SERIAL_PORT /dev/ttyACM0)
set(SIZE_OUTPUT "-d")