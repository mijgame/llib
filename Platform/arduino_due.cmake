# Targets
set(TARGET_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/targets/due")
set(CHIP_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/targets/sam3x8e")

# Target specific sources
set(TARGET_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/targets/sam3x8e/wait.cpp"
        boot/sam3x8e/startup.c
        targets/sam3x8e/startup.c
        targets/sam3x8e/stream_target.cpp
        targets/sam3x8e/tc_interrupt.cpp
        targets/sam3x8e/interrupt.cpp
)

# Vendor specific includes
set(VENDOR_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/cortex/atmel")

# Linkerscript for Arduino Due
set(LINKERSCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/boot/sam3x8e/linkerscript.ld")

# Cpu flags for the due
set(TARGET_CPU_FLAGS "-D__SAM3X8E__ -Os -mcpu=cortex-m3 -march=armv7-m -mthumb")

set(LLIB_TARGET "sam3x8e")