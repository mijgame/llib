# Target specific includes
set(TARGET_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/targets/tests")

# Target specific sources
set(TARGET_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/targets/tests/wait.cpp"
                    targets/tests/stream_target.cpp
)

# Cpu flags for the tests
set(TARGET_CPU_FLAGS "")

