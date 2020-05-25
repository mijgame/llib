# Targets
set(TARGET_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/targets/boards/due")
set(CHIP_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/targets/chips/sam3x8e")

# Target specific sources
set(TARGET_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/targets/chips/sam3x8e/wait.cpp"
        boot/sam3x8e/startup.c
        targets/chips/sam3x8e/startup.c
        targets/chips/sam3x8e/stream_target.cpp
        targets/chips/sam3x8e/tc_interrupt.cpp
        targets/chips/sam3x8e/interrupt.cpp
        targets/chips/sam3x8e/uotghs.cpp
)

# Vendor specific includes
set(VENDOR_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/cortex/atmel")

# Linkerscript for Arduino Due
set(LINKERSCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/boot/sam3x8e/linkerscript.ld")

# Cpu flags for the due
set(TARGET_CPU_FLAGS "-D__SAM3X8E__ -Os -mcpu=cortex-m3 -march=armv7-m -mthumb")

set(LLIB_TARGET "sam3x8e")
set(LLIB_BOARD "due")