# CMake requirements.
cmake_minimum_required(VERSION 3.7...3.24.2)

# ============================================================================ #
#
#                 				Add tests to project
#
# ============================================================================ #

# does the application run
add_test(NAME Runs COMMAND Main.exe)
