# Targets
set(TARGET_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/targets/due")

# Target specific sources
set(TARGET_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/targets/due/wait.cpp"
        boot/due/startup.c
        targets/due/startup.c
        targets/due/stream_target.cpp
        targets/due/tc_interrupt.cpp
        targets/due/interrupt.cpp
)

# Linkerscript for Arduino Due
set(TARGET_LINKERSCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/boot/due/linkerscript.ld")
set(CORTEX_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/cortex/atmel")
set(TARGET_LINKERSCRIPT_INCLUDE "${CORTEX_INCLUDE}/sam3xa/source/as_gcc")

# Cpu flags for the due
set(TARGET_CPU_FLAGS "-D__SAM3X8E__ -Os -mcpu=cortex-m3 -march=armv7-m -mthumb")

