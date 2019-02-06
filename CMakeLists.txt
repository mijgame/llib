cmake_minimum_required(VERSION 3.11)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR cortex-m3)

set(SERIAL_PORT /dev/ttyACM0)

if (WIN32)
    set(OBJCOPY "C:/SysGCC/arm-eabi/bin/arm-eabi-objcopy")
    set(CMAKE_C_COMPILER C:/SysGCC/arm-eabi/bin/arm-eabi-gcc.exe)
    set(CMAKE_CXX_COMPILER C:/SysGCC/arm-eabi/bin/arm-eabi-g++.exe)
elseif(APPLE)
    set(OBJCOPY "/opt/arm-none-eabi/bin/arm-none-eabi-objcopy")
    set(CMAKE_C_COMPILER "/opt/arm-none-eabi/bin/arm-none-eabi-gcc")
    set(CMAKE_CXX_COMPILER "/opt/arm-none-eabi/bin/arm-none-eabi-g++")
else ()
    set(OBJCOPY "$ENV{HOME}/opt/gcc-arm-none-eabi-7-2018-q2-update/bin/arm-none-eabi-objcopy")
    set(CMAKE_C_COMPILER "$ENV{HOME}/opt/gcc-arm-none-eabi-7-2018-q2-update/bin/arm-none-eabi-gcc")
    set(CMAKE_CXX_COMPILER "$ENV{HOME}/opt/gcc-arm-none-eabi-7-2018-q2-update/bin/arm-none-eabi-g++")
    set(TERMINAL "${CMAKE_CURRENT_SOURCE_DIR}/tools/lpc21isp_197/lpc21isp_hr_linux")
    set(BOSSAC "bossac")
endif ()

# Cortex header files include directory
set(CORTEX_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/cortex/atmel")
set(AS_GCC "${CORTEX_INCLUDE}/sam3xa/source/as_gcc")

# Targets
set(TARGET_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/targets/due")
set(TARGET_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/targets/due/wait.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/targets/due/stream_target.cpp")
set(TARGET_STARTUP "${CMAKE_CURRENT_SOURCE_DIR}/targets/due/startup.c")

# Linkerscript for Arduino Due
set(LINKERSCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/boot/linkerscript.ld")

# Startup & system options
set(BOOT_SOURCES boot/startup.c main.cpp boot/stack.c boot/polyfill.c)
set(ROM_START 0x00000000)
set(ROM_SIZE 512k)
set(RAM_START 0x20070000)
set(RAM_SIZE 96k)
set(STACK_SIZE 73728)

# Supress Error when trying to test the compiler
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(BUILD_SHARED_LIBS OFF)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(COMMON_FLAGS "-D__SAM3X8E__ -Os -mcpu=cortex-m3 -march=armv7-m -mthumb -Wall -Werror -Wno-maybe-uninitialized -Wno-unused-local-typedefs -Wno-unused-but-set-variable -Wno-unused-local-typedefs -Wno-unused-function -Wno-attributes -Werror -fno-exceptions -fno-non-call-exceptions -fno-common -ffunction-sections -fdata-sections -fno-exceptions -fno-asynchronous-unwind-tables -fomit-frame-pointer -fdata-sections -ffunction-sections -nostdlib")
set(CXX_FLAGS "-std=c++17 -fno-rtti -fno-threadsafe-statics -fno-use-cxa-get-exception-ptr")
set(C_FLAGS "-std=c11")
set(LINKER_FLAGS "-I${AS_GCC} -T ${LINKERSCRIPT_PATH} -lgcc -Wl,--gc-sections -Wl,-fatal-warnings -nostdlib -nodefaultlibs -nostartfiles") #

project(llib)

# Flags
set(CMAKE_C_FLAGS_DEBUG "${COMMON_FLAGS} ${C_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE "${COMMON_FLAGS} ${C_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${COMMON_FLAGS} ${CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${COMMON_FLAGS} ${CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${COMMON_FLAGS} ${LINKER_FLAGS}")

set(CMAKE_CXX_STANDARD 17)

set(LLIB_HEADERS llib/peripheral.hpp llib/stream.hpp llib/stream_base.hpp llib/bitset.hpp llib/dynamic_array.hpp llib/queue.hpp llib/list.hpp llib/defines.hpp llib/math.hpp llib/wait.hpp llib/string.hpp)

add_executable(llib ${BOOT_SOURCES} ${LLIB_HEADERS} ${TARGET_INCLUDE} ${TARGET_STARTUP} ${TARGET_SOURCES})
add_custom_command(TARGET llib POST_BUILD COMMAND ${OBJCOPY} ARGS -O binary -R .bss llib llib.bin)

target_link_libraries(llib "gcc")
target_include_directories(llib PRIVATE ${CORTEX_INCLUDE})
target_include_directories(llib PRIVATE ${TARGET_INCLUDE})
target_include_directories(llib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/llib)
target_include_directories(llib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/targets/due)