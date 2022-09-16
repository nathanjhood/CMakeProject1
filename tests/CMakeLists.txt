# CMake requirements.
cmake_minimum_required(VERSION 3.7...3.24)

# ============================================================================ #
#
#                 Add tests to target: CMakeProject1-executable
#
# ============================================================================ #

enable_testing()

# does the application run
add_test(NAME Runs COMMAND ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}-Executable)
