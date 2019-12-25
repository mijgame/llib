cmake_minimum_required(VERSION 3.12)

# Include the target we want to compile for
include("./Platform/mcb2130.cmake")

# Use the toolchain of cmake to include the correct compiler stuff
set(CMAKE_TOOLCHAIN_FILE "./Platform/toolchain-arm-eabi.cmake")

# Cortex header files include directory
set(BRIGAND_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/brigand")

# Startup & system options
set(BOOT_SOURCES main.cpp ${BOOT_SOURCES} ${TARGET_BOOT_SOURCES})

# enable assembly
enable_language(ASM)

# The project name
project(llib)

# Llib header files
set(LLIB_HEADERS
        llib/peripheral.hpp
        llib/stream.hpp
        llib/servo.hpp
        llib/stream_base.hpp
        llib/bitset.hpp
        llib/dynamic_array.hpp
        llib/queue.hpp
        llib/defines.hpp
        llib/math.hpp
        llib/wait.hpp
        llib/string.hpp
        llib/decorators.hpp
        llib/ports.hpp
        llib/ringbuffer.hpp
        llib/displays/display_32x32.hpp
        llib/displays/ssd1306.hpp
        llib/displays/strategy.hpp
        llib/displays/display_ostream.hpp
        llib/graphics/color.hpp
        llib/graphics/font.hpp
        llib/graphics/image.hpp
        llib/vector2.hpp
        llib/streams/combined_stream.hpp
        llib/io/pfc8574.hpp
        llib/analog/pcf8591.hpp
        llib/units.hpp llib/transaction.hpp)

# Rtos source and header files
# set(LLIB_RTOS_HEADERS rtos/rtos.hpp rtos/promise.hpp rtos/thread.hpp)
# set(LLIB_RTOS_SOURCES rtos/rtos.cpp rtos/switch_task.asm)

# Add the llib executable with all the headers and sources
add_executable(llib ${BOOT_SOURCES} ${LLIB_HEADERS} ${TARGET_INCLUDE} ${TARGET_STARTUP} ${TARGET_SOURCES} ${LLIB_RTOS_HEADERS} ${LLIB_RTOS_SOURCES})

# Custom commands for processing the build binary and show some statistics and debug info 
add_custom_command(TARGET llib POST_BUILD COMMAND ${CMAKE_OBJCOPY} ARGS -O binary -R .bss -R .stack llib llib.bin)
add_custom_command(TARGET llib POST_BUILD COMMAND ${CMAKE_OBJDUMP} ARGS -S llib > llib.lss)
add_custom_command(TARGET llib POST_BUILD COMMAND ${CMAKE_OBSIZE} ARGS -A llib -x)

# Disable Boost support for Brigand
add_compile_definitions(BRIGAND_NO_BOOST_SUPPORT)

# Libraries to link for all targets
link_libraries(llib "m")
link_libraries(llib "gcc")

# Include directories for all targets
include_directories(PRIVATE ${VENDOR_INCLUDE})
include_directories(PRIVATE ${BRIGAND_INCLUDE})
include_directories(PRIVATE ${TARGET_INCLUDE})
include_directories(PRIVATE ${CHIP_INCLUDE})
include_directories(PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/llib)
include_directories(PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/targets)
include_directories(PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

