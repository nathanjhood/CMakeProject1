# CMake requirements.
cmake_minimum_required(VERSION 3.7...3.24)

find_package(Git)
if(GIT_FOUND AND EXISTS ${PROJECT_SOURCE_DIR}/.git)
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Running: git submodule update --init")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "Error: git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        else()
            message(STATUS "Complete: git submodules are up to date")
        endif()
    endif()
endif()

# Toolchain location. Stores result in the CMakeCache.
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)
    message(ERROR "Error: vcpkg not found locally - using: ${CMAKE_TOOLCHAIN_FILE}")
else()
    set(CMAKE_TOOLCHAIN_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Toolchain file")
    message(STATUS "Toolchain: Using vcpkg found at: ${CMAKE_TOOLCHAIN_FILE}")
endif()
