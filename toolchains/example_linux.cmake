# compiler settings
set(CMAKE_C_COMPILER "$ENV{HOME}/opt/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "$ENV{HOME}/opt/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi-g++")

# arm-eabi
set(ARM_EABI_OBJCOPY "$ENV{HOME}/opt/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi-objcopy")
set(ARM_EABI_OBJDUMP "$ENV{HOME}/opt/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi-objdump")
set(ARM_EABI_SIZE "$ENV{HOME}/opt/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi-size")

# other settings
set(TERMINAL "${CMAKE_CURRENT_SOURCE_DIR}/tools/lpc21isp_197/lpc21isp_hr_linux" CACHE STRING "" FORCE)
set(BOSSAC "bossac" CACHE STRING "" FORCE)
set(SERIAL_PORT /dev/ttyACM0 CACHE STRING "" FORCE)
set(SIZE_OUTPUT "-d" CACHE STRING "" FORCE)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(BUILD_SHARED_LIBS OFF)

# TODO
# This SHOULD be put in a shared file, but cmake is a general
# piece of shit and screams when you try to include a file here
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR cortex-m3)

set(CORTEX_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/cortex/atmel")
set(AS_GCC "${CORTEX_INCLUDE}/sam3xa/source/as_gcc")

set(COMMON_FLAGS "-D__SAM3X8E__ -Os -mcpu=cortex-m3 -march=armv7-m -mthumb -Wall -Werror -Wno-maybe-uninitialized -Wno-unused-local-typedefs -Wno-unused-but-set-variable -Wno-unused-local-typedefs -Wno-unused-function -Wno-attributes -Werror -fno-exceptions -fno-non-call-exceptions -fno-common -ffunction-sections -fdata-sections -fno-exceptions -fno-asynchronous-unwind-tables -fomit-frame-pointer -fdata-sections -ffunction-sections -nostdlib")
set(CXX_FLAGS "-std=c++17 -fconcepts -fno-rtti -fno-threadsafe-statics -fno-use-cxa-get-exception-ptr")

set(C_FLAGS "-std=c11")
set(LINKER_FLAGS "-I${AS_GCC} -T ${LINKERSCRIPT_PATH} -lm -lgcc -Wl,--gc-sections -Wl,-fatal-warnings -Wl,-Map=llib.map -nostdlib -nodefaultlibs -nostartfiles")
set(ASM_FLAGS "-x assembler-with-cpp")

set(CMAKE_C_FLAGS_DEBUG "${COMMON_FLAGS} ${C_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELEASE "${COMMON_FLAGS} ${C_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "${COMMON_FLAGS} ${CXX_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "${COMMON_FLAGS} ${CXX_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "${COMMON_FLAGS} ${LINKER_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_ASM_FLAGS "${COMMON_FLAGS} ${C_FLAGS} ${ASM_FLAGS}" CACHE STRING "" FORCE)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)