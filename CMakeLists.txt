cmake_minimum_required(VERSION 3.12)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR cortex-m3)

# Startup & system options
set(BOOT_SOURCES boot/startup.c)
set(ROM_START 0x00000000)
set(ROM_SIZE 512k)
set(RAM_START 0x20000000)
set(RAM_SIZE 96k)
set(STACK_SIZE 73728)

# Supress Error when trying to test the compiler
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(BUILD_SHARED_LIBS OFF)

# Set compiler
set(CMAKE_C_COMPILER C:/SysGCC/arm-eabi/bin/arm-eabi-gcc.exe)
set(CMAKE_CXX_COMPILER C:/SysGCC/arm-eabi/bin/arm-eabi-g++.exe)

set(CMAKE_FIND_ROOT_PATH C:/SysGCC/arm-eabi)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(COMMON_FLAGS " -D__SAM3X8E__  -Os -mcpu=cortex-m3 -mthumb -Wall -Werror -fno-exceptions -fno-non-call-exceptions -fno-common -ffunction-sections -fdata-sections -fstack-protector-strong -findirect-inlining -fno-exceptions -fno-asynchronous-unwind-tables -fomit-frame-pointer")
set(CXX_FLAGS "-fno-rtti -fno-threadsafe-statics -fno-use-cxa-get-exception-ptr")
set(LINKER_FLAGS "-nostdlib -nodefaultlibs -IC:/ti-software/bmptk/targets/cortex/atmel/sam3xa/source/as_gcc -DROM_START=${ROM_START} -DROM_SIZE=${ROM_SIZE} -DRAM_START=${RAM_START} -DRAM_SIZE=${RAM_SIZE} -T C:/ti-software/llib/boot/linkerscript.ld")

project(llib)

# Flags
set(CMAKE_C_FLAGS ${COMMON_FLAGS})
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} ${CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS}")

set(CMAKE_CXX_STANDARD 17)

add_executable(llib ${BOOT_SOURCES} main.cpp lib/peripheral.hpp lib/pins.hpp lib/pio.hpp lib/uart.hpp)
target_include_directories(llib PRIVATE C:/ti-software/bmptk/targets/cortex/atmel)