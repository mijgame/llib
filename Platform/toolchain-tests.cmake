# Originally from:
#   http://www.valvers.com/open-software/raspberry-pi/step03-bare-metal-programming-in-c-pt3/
# A CMake toolchain file for cross-compilation

include(CMakeForceCompiler)

# usage
# cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain-arm-eabi.cmake ../

# The Generic system name is used for embedded targets (targets without OS) in
# CMake
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR x86)

# Set a toolchain path. You only need to set this if the toolchain isn't in
# your system path. Don't forget a trailing path separator!
set(TC_PATH "")

# Supress Error when trying to test the compiler
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(BUILD_SHARED_LIBS OFF)

# specify the compiler. We force the compiler so that CMake doesn't
# attempt to build a simple test program as this will fail without us using
# the -nostartfiles option on the command line
set(CMAKE_C_COMPILER ${TC_PATH}gcc)
set(CMAKE_CXX_COMPILER ${TC_PATH}g++)

set(CMAKE_OBJCOPY echo
      CACHE FILEPATH "The toolchain objcopy command " FORCE)

set(CMAKE_OBJDUMP echo
      CACHE FILEPATH "The toolchain objdump command " FORCE)

set(CMAKE_OBSIZE echo
      CACHE FILEPATH "The toolchain size command " FORCE)

# Toolchain flags
set(COMMON_FLAGS "${COMMON_FLAGS} ${TARGET_CPU_FLAGS}")

# boot sources
set(BOOT_SOURCES ${BOOT_SOURCES} CACHE STRING "")

# Other compiler flags
set(CXX_FLAGS "-std=c++17 -fconcepts -fno-rtti -fno-threadsafe-statics -fno-use-cxa-get-exception-ptr")
set(C_FLAGS "-std=c11")
set(ASM_FLAGS "-x assembler-with-cpp")
set(DEBUG_FLAGS "-g")

set(CMAKE_CXX_STANDARD 17)

# Linker settings
set(LINKER_FLAGS "-lm -lgcc -Wl,--gc-sections -Wl,-fatal-warnings -Wl,-Map=llib.map")

# Compiler flags
set(CMAKE_C_FLAGS_DEBUG "${COMMON_FLAGS} ${C_FLAGS} ${DEBUG_FLAGS}" CACHE STRING "")
set(CMAKE_C_FLAGS_RELEASE "${COMMON_FLAGS} ${C_FLAGS}" CACHE STRING "")

set(CMAKE_CXX_FLAGS_DEBUG "${COMMON_FLAGS} ${CXX_FLAGS} ${DEBUG_FLAGS}" CACHE STRING "")
set(CMAKE_CXX_FLAGS_RELEASE "${COMMON_FLAGS} ${CXX_FLAGS}" CACHE STRING "")

set(CMAKE_ASM_FLAGS "${COMMON_FLAGS} ${C_FLAGS} ${ASM_FLAGS}" CACHE STRING "")

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS "${COMMON_FLAGS} ${LINKER_FLAGS}" CACHE STRING "")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
