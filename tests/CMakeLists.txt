# CMake requirements.
cmake_minimum_required(VERSION 3.7...3.24.2)

# ============================================================================ #
#
#                 				Add tests to project
#
# ============================================================================ #

#enable CMake-style tests
enable_testing()

# does the application run
include(${CMAKE_CURRENT_LIST_DIR}/run_from_bin_tree.cmake)
