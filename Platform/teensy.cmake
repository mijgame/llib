# Target specific includes
set(TARGET_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/targets/boards/teensy")
set(CHIP_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/targets/chips/imx1062")

# Target specific sources
set(TARGET_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/targets/chips/imx1062/wait.cpp"
        boot/imx1062/startup.c
        boot/imx1062/flash.c
        targets/chips/imx1062/startup.c
        vendor/cortex/nxp/boards/evkmimxrt1060/xip/evkmimxrt1060_flexspi_nor_config.c
)

# Vendor specific includes
set(VENDOR_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/cortex/nxp/boards/evkmimxrt1060/xip"
        "vendor/cortex/nxp/devices/MIMXRT1062/drivers"
        "vendor/cortex/nxp/devices/MIMXRT1062/"
        "vendor/cortex/nxp/CMSIS/Include"
)

# Linkerscript for the Teensy
set(LINKERSCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/boot/imx1062/linkerscript.ld")

# Cpu flags for the teensy
set(TARGET_CPU_FLAGS "-DCPU_MIMXRT1062DVL6A")

set(LLIB_TARGET "imx1062")