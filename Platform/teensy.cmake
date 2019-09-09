# Target specific includes
set(TARGET_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/targets/teensy")

# Target specific sources
set(TARGET_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/targets/teensy/wait.cpp"
        boot/teensy/startup.c
        targets/teensy/startup.c
)

# Linkerscript for the Teensy
set(TARGET_LINKERSCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/boot/teensy/linkerscript.ld")

# Cpu flags for the teensy
set(TARGET_CPU_FLAGS "")

