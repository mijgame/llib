# Targets
set(TARGET_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/targets/due")
set(CHIP_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/targets/lpc2138")

# Target specific sources
set(TARGET_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/targets/lpc2138/wait.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/boot/lpc2138/startup.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/boot/lpc2138/startup.s"
        "${CMAKE_CURRENT_SOURCE_DIR}/targets/lpc2138/startup.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/targets/lpc2138/stream_target.cpp"
)

# Vendor specific includes
set(VENDOR_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/cortex/nxp")

# Linkerscript for Arduino Due
set(LINKERSCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/boot/lpc2138/linkerscript.ld")

# Cpu flags for the due
set(TARGET_CPU_FLAGS "-Os -mcpu=arm7tdmi-s -march=armv4t") # -mthumb

set(LLIB_TARGET "lpc2138")