# Targets
set(TARGET_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/targets/boards/mcb2130")
set(CHIP_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/targets/chips/lpc2138")

# Target specific sources
set(TARGET_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/targets/chips/lpc2138/wait.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/boot/lpc2138/startup.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/boot/lpc2138/startup.s"
        "${CMAKE_CURRENT_SOURCE_DIR}/targets/chips/lpc2138/startup.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/targets/chips/lpc2138/stream_target.cpp"
)

# Vendor specific includes
set(VENDOR_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/cortex/nxp")

# Linkerscript for the lpc2138
set(LINKERSCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/boot/lpc2138/linkerscript.ld")

# Cpu flags for the lpc2138 (thumb mode is supported)
set(TARGET_CPU_FLAGS "-Os -mcpu=arm7tdmi-s -march=armv4t -mthumb") #

set(LLIB_TARGET "lpc2138")
set(LLIB_BOARD "mcb2130")