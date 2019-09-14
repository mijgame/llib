# Target specific includes
set(TARGET_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/targets/teensy" 
                   "vendor/cortex/nxp/boards/evkmimxrt1060/xip"
                   "vendor/cortex/nxp/devices/MIMXRT1062/drivers"
                   "vendor/cortex/nxp/devices/MIMXRT1062/"
                   "vendor/cortex/nxp/CMSIS/Include"
)

# Target specific sources
set(TARGET_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/targets/teensy/wait.cpp"
        boot/teensy/startup.c
        boot/teensy/flash.c
        targets/teensy/startup.c
        vendor/cortex/nxp/boards/evkmimxrt1060/xip/evkmimxrt1060_flexspi_nor_config.c
        
)

# Linkerscript for the Teensy
set(TARGET_LINKERSCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/boot/teensy/linkerscript.ld")

# Cpu flags for the teensy
set(TARGET_CPU_FLAGS "-DCPU_MIMXRT1062CVJ5A")

