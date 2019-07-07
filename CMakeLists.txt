#############################
#
#  !! Please do not forget to include the right toolchain using !!
#     -DCMAKE_TOOLCHAIN_FILE=path/to/file
#
#############################

cmake_minimum_required(VERSION 3.12)

set(BRIGAND_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/brigand")
set(CATCH_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/catch2")
set(CORTEX_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/cortex/atmel")
set(AS_GCC "${CORTEX_INCLUDE}/sam3xa/source/as_gcc")

project(llib)

# Targets
set(TARGET_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/targets/due")
set(TARGET_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/targets/due/wait.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/targets/due/stream_target.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/targets/due/tc_interrupt.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/targets/due/interrupt.cpp"
)

set(TARGET_STARTUP "${CMAKE_CURRENT_SOURCE_DIR}/targets/due/startup.c")

# Linkerscript for Arduino Due
set(LINKERSCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/boot/linkerscript.ld")

# Startup & system options
set(BOOT_SOURCES boot/startup.c main.cpp boot/polyfill.c targets/due/interrupt.cpp targets/due/tc_interrupt.cpp)

# Supress Error when trying to test the compiler
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(BUILD_SHARED_LIBS OFF)

set(CMAKE_CXX_STANDARD 17)

# Enable assembly
enable_language(ASM)

# Main library
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

# RTOS
set(LLIB_RTOS_HEADERS rtos/rtos.hpp rtos/promise.hpp rtos/thread.hpp)
set(LLIB_RTOS_SOURCES rtos/rtos.cpp rtos/switch_task.asm)

# Tests
file(GLOB LLIB_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)

add_executable(llib ${BOOT_SOURCES} ${LLIB_HEADERS} ${TARGET_INCLUDE} ${TARGET_STARTUP} ${TARGET_SOURCES} ${LLIB_RTOS_HEADERS} ${LLIB_RTOS_SOURCES})
add_executable(llib_tests ${LLIB_TEST_SOURCES})

# TODO: extract these commands to allow for multiple targets
add_custom_command(TARGET llib POST_BUILD COMMAND ${ARM_EABI_OBJCOPY} ARGS -O binary -R .bss -R .stack llib llib.bin)
add_custom_command(TARGET llib POST_BUILD COMMAND ${ARM_EABI_OBJDUMP} ARGS -S llib > llib.lss)
add_custom_command(TARGET llib POST_BUILD COMMAND ${ARM_EABI_SIZE} ARGS -A llib ${SIZE_OUTPUT})

# Disable Boost support for Brigand
add_compile_definitions(BRIGAND_NO_BOOST_SUPPORT)


link_directories("$ENV{HOME}/opt/gcc-arm-none-eabi-8-2018-q4-major")

# Main application
target_link_libraries(llib "m")
target_link_libraries(llib "gcc")
target_include_directories(llib PRIVATE ${CORTEX_INCLUDE})
target_include_directories(llib PRIVATE ${BRIGAND_INCLUDE})
target_include_directories(llib PRIVATE ${TARGET_INCLUDE})
target_include_directories(llib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/llib)
target_include_directories(llib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/targets/due)

# Tests
target_include_directories(llib_tests PRIVATE ${BRIGAND_INCLUDE})
target_include_directories(llib_tests PRIVATE ${CATCH_INCLUDE})
target_include_directories(llib_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/llib)