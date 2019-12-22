# Targets
set(TARGET_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/targets/due")
set(CHIP_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/targets/lpc2138")

# Target specific sources
set(TARGET_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/targets/lpc2138/wait.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/boot/lpc2138/startup.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/targets/lpc2138/startup.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/targets/lpc2138/stream_target.cpp"
)

# Vendor specific includes
set(VENDOR_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/cortex/atmel")

# Linkerscript for Arduino Due
set(LINKERSCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/boot/lpc2138/linkerscript.ld")

# Cpu flags for the due
set(TARGET_CPU_FLAGS "-Os -mcpu=cortex-m3 -march=armv7-m -mthumb")

set(LLIB_TARGET "lpc2138")