cmake_minimum_required(VERSION 3.11)

# compiler settings
set(CMAKE_C_COMPILER "C:/SysGCC/arm-none-eabi/bin/arm-none-eabi-gcc.exe")
set(CMAKE_CXX_COMPILER "C:/SysGCC/arm-none-eabi/bin/arm-none-eabi-g++.exe")

# arm-eabi
set(ARM_EABI_OBJCOPY "C:/SysGCC/arm-none-eabi/bin/arm-none-eabi-objcopy.exe")
set(ARM_EABI_OBJDUMP "C:/SysGCC/arm-none-eabi/bin/arm-none-eabi-objdump.exe")
set(ARM_EABI_SIZE "C:/SysGCC/arm-none-eabi/bin/arm-none-eabi-size.exe") 

# other settings
set(SIZE_OUTPUT "-d")

include("${CMAKE_CURRENT_SOURCE_DIR}/flags.cmake")