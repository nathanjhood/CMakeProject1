# CMake requirements.
cmake_minimum_required(VERSION 3.7...3.24.2)

# ============================================================================ #
#
#                 Add tests to target: CMakeProject1-executable
#
# ============================================================================ #

enable_testing()

#include(run_from_bin_tree)

# does the application run
add_test(NAME Runs COMMAND ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}-Executable)
