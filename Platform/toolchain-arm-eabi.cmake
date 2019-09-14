# Originally from:
#   http://www.valvers.com/open-software/raspberry-pi/step03-bare-metal-programming-in-c-pt3/
# A CMake toolchain file for cross-compilation

include(CMakeForceCompiler)

# usage
# cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain-arm-eabi.cmake ../

# The Generic system name is used for embedded targets (targets without OS) in
# CMake
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

# Set a toolchain path. You only need to set this if the toolchain isn't in
# your system path. Don't forget a trailing path separator!
set(TC_PATH "")

# The toolchain prefix for all toolchain executables
set(CROSS_COMPILE arm-none-eabi-)

# Supress Error when trying to test the compiler
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(BUILD_SHARED_LIBS OFF)

# specify the cross compiler. We force the compiler so that CMake doesn't
# attempt to build a simple test program as this will fail without us using
# the -nostartfiles option on the command line
set(CMAKE_C_COMPILER ${TC_PATH}${CROSS_COMPILE}gcc)
set(CMAKE_CXX_COMPILER ${TC_PATH}${CROSS_COMPILE}g++)

# The cross linker
set(CMAKE_LINKER ${TC_PATH}${CROSS_COMPILE}ld
      CACHE FILEPATH "The toolchain linker command " FORCE)

# We must set the OBJCOPY setting into cache so that it's available to the
# whole project. Otherwise, this does not get set into the CACHE and therefore
# the build doesn't know what the OBJCOPY filepath is
set(CMAKE_OBJCOPY ${TC_PATH}${CROSS_COMPILE}objcopy
      CACHE FILEPATH "The toolchain objcopy command " FORCE)

set(CMAKE_OBJDUMP ${TC_PATH}${CROSS_COMPILE}objdump
      CACHE FILEPATH "The toolchain objdump command " FORCE)

set(CMAKE_OBSIZE ${TC_PATH}${CROSS_COMPILE}size
      CACHE FILEPATH "The toolchain size command " FORCE)

# Toolchain flags
set(COMMON_FLAGS "${COMMON_FLAGS} -Wall -Werror -Wno-maybe-uninitialized -Wno-unused-local-typedefs -Wno-unused-but-set-variable")
set(COMMON_FLAGS "${COMMON_FLAGS} -Wno-unused-local-typedefs -Wno-unused-function -Wno-attributes -Werror -fno-exceptions")
set(COMMON_FLAGS "${COMMON_FLAGS} -fno-non-call-exceptions -fno-common -ffunction-sections -fdata-sections -fno-exceptions")
set(COMMON_FLAGS "${COMMON_FLAGS} -fno-asynchronous-unwind-tables -fomit-frame-pointer -fdata-sections -ffunction-sections -nostdlib")
set(COMMON_FLAGS "${COMMON_FLAGS} ${TARGET_CPU_FLAGS}")

# boot sources
set(BOOT_SOURCES ${BOOT_SOURCES} boot/polyfill.c)


# Other compiler flags
set(CXX_FLAGS "-std=c++17 -fconcepts -fno-rtti -fno-threadsafe-statics -fno-use-cxa-get-exception-ptr")
set(C_FLAGS "-std=c11")
set(ASM_FLAGS "-x assembler-with-cpp")
set(DEBUG_FLAGS "-g")

set(CMAKE_CXX_STANDARD 17)

# Linker settings
set(LINKER_FLAGS "${LINKER_FLAGS} -I${TARGET_LINKERSCRIPT_INCLUDE} -T ${TARGET_LINKERSCRIPT_PATH}")
set(LINKER_FLAGS "${LINKER_FLAGS} -lm -lgcc -Wl,--gc-sections -Wl,-fatal-warnings -Wl,-Map=llib.map -nostdlib -nodefaultlibs -nostartfiles")

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
