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

# Set the CMAKE C and CXX flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)