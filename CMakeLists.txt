cmake_minimum_required(VERSION 3.12)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR cortex-m3)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/toolchains/toolchain.cmake")
        message("Using Custom Toolchain file")
        include("${CMAKE_CURRENT_SOURCE_DIR}/toolchains/toolchain.cmake")
else()
        string(TOLOWER ${CMAKE_HOST_SYSTEM_NAME} llib_host)
        message("Using example toolchain file for Host: ${llib_host}" )
        include("${CMAKE_CURRENT_SOURCE_DIR}/toolchains/example_${llib_host}.cmake")
endif ()

# Cortex header files include directory
set(CORTEX_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/cortex/atmel")
set(BRIGAND_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/brigand")
set(AS_GCC "${CORTEX_INCLUDE}/sam3xa/source/as_gcc")

# Targets
set(TARGET_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/targets/due")
set(TARGET_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/targets/due/wait.cpp"
        targets/due/stream_target.cpp
        targets/due/tc_interrupt.cpp
        targets/due/interrupt.cpp
)

set(TARGET_STARTUP "${CMAKE_CURRENT_SOURCE_DIR}/targets/due/startup.c")

# Linkerscript for Arduino Due
set(LINKERSCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/boot/linkerscript.ld")

# Startup & system options
set(BOOT_SOURCES boot/startup.c main.cpp boot/polyfill.c targets/due/interrupt.cpp targets/due/tc_interrupt.cpp)

# Supress Error when trying to test the compiler
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(BUILD_SHARED_LIBS OFF)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(COMMON_FLAGS "-D__SAM3X8E__ -Os -mcpu=cortex-m3 -march=armv7-m -mthumb -Wall -Werror -Wno-maybe-uninitialized -Wno-unused-local-typedefs -Wno-unused-but-set-variable -Wno-unused-local-typedefs -Wno-unused-function -Wno-attributes -Werror -fno-exceptions -fno-non-call-exceptions -fno-common -ffunction-sections -fdata-sections -fno-exceptions -fno-asynchronous-unwind-tables -fomit-frame-pointer -fdata-sections -ffunction-sections -nostdlib")
set(CXX_FLAGS "-std=c++17 -fconcepts -fno-rtti -fno-threadsafe-statics -fno-use-cxa-get-exception-ptr")

set(C_FLAGS "-std=c11")
set(LINKER_FLAGS "-I${AS_GCC} -T ${LINKERSCRIPT_PATH} -lm -lgcc -Wl,--gc-sections -Wl,-fatal-warnings -Wl,-Map=llib.map -nostdlib -nodefaultlibs -nostartfiles")
set(ASM_FLAGS "-x assembler-with-cpp")

project(llib)

# Flags
set(CMAKE_C_FLAGS_DEBUG "${COMMON_FLAGS} ${C_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE "${COMMON_FLAGS} ${C_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${COMMON_FLAGS} ${CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${COMMON_FLAGS} ${CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${COMMON_FLAGS} ${LINKER_FLAGS}")
set(CMAKE_ASM_FLAGS "${COMMON_FLAGS} ${C_FLAGS} ${ASM_FLAGS}")

set(CMAKE_CXX_STANDARD 17)

# enable assembly
enable_language(ASM)

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
        llib/units.hpp llib/transaction.hpp llib/flyweight_array.hpp)

set(LLIB_RTOS_HEADERS rtos/rtos.hpp rtos/promise.hpp rtos/thread.hpp)
set(LLIB_RTOS_SOURCES rtos/rtos.cpp rtos/switch_task.asm)

add_executable(llib ${BOOT_SOURCES} ${LLIB_HEADERS} ${TARGET_INCLUDE} ${TARGET_STARTUP} ${TARGET_SOURCES} ${LLIB_RTOS_HEADERS} ${LLIB_RTOS_SOURCES})

add_custom_command(TARGET llib POST_BUILD COMMAND ${ARM_EABI_OBJCOPY} ARGS -O binary -R .bss -R .stack llib llib.bin)
add_custom_command(TARGET llib POST_BUILD COMMAND ${ARM_EABI_OBJDUMP} ARGS -S llib > llib.lss)
add_custom_command(TARGET llib POST_BUILD COMMAND ${ARM_EABI_SIZE} ARGS -A llib ${SIZE_OUTPUT})

# Disable Boost support for Brigand
add_compile_definitions(BRIGAND_NO_BOOST_SUPPORT)

target_link_libraries(llib "m")
target_link_libraries(llib "gcc")
target_include_directories(llib PRIVATE ${CORTEX_INCLUDE})
target_include_directories(llib PRIVATE ${BRIGAND_INCLUDE})
target_include_directories(llib PRIVATE ${TARGET_INCLUDE})
target_include_directories(llib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/llib)
target_include_directories(llib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/targets/due)
