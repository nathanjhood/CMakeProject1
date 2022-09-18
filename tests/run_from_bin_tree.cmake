# CMake requirements.
cmake_minimum_required(VERSION 3.7...3.24.2)

# does the application run
add_test(NAME Runs COMMAND ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}-Executable)
