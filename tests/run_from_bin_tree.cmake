# CMake requirements.
cmake_minimum_required(VERSION 3.7...3.24.2)

# ============================================================================ #
#
#                 		Add test: Run from build tree
#
# ============================================================================ #

# does the application run
add_test(NAME Runs COMMAND Main.exe)
