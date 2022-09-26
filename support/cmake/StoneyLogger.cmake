# ============================================================================ #
#
# @file StoneyLogger.cmake
#
# @author Nathan J. Hood ( @StoneyDSP )
# @brief
# @version 1.0.0.0
# @date 2022-08-23
#
# @copyright Copyright (c) 2022
#
# ============================================================================ #

# CMake requirements.
cmake_minimum_required(VERSION 3.7...3.24.2)

# ============================================================================ #
#
#                             Configure CMake
#
# ============================================================================ #

message("\n")
message(STATUS "${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt>\n")
message(STATUS "CMake found at: ${CMAKE_COMMAND}\n")
message(STATUS "Initiating CMake v${CMAKE_VERSION}\n")
message("\n")

message("Options:\n")
message("CMAKE_PROJECT_VENDOR = " ${CMAKE_PROJECT_VENDOR})
message("ENABLE_LOGGING = " ${ENABLE_LOGGING})
message("USE_EXTERN = " ${USE_EXTERN})
message("GIT_SUBMODULE = " ${GIT_SUBMODULE})
message("USE_VCPKG = " ${USE_VCPKG})
message("USE_FOO = " ${USE_FOO})
message("USE_TESTS = " ${USE_TESTS})
message("BUILD_SHARED_LIBS = " ${BUILD_SHARED_LIBS})
message("ASAN_ENABLED = " ${ASAN_ENABLED})
message("\n")

# ============================================================================ #
#
#                           Configure Dependencies
#
# ============================================================================ #

# ============================================================================ #
#
#                           Create New Project
#
# ============================================================================ #

message("Detecting CMake project...\n")
message(STATUS "...Detected project:\n")
message("${PROJECT_NAME} v${PROJECT_VERSION}")
message("${PROJECT_DESCRIPTION}")
message("${PROJECT_HOMEPAGE_URL}")
message("@ ${PROJECT_VENDOR}\n")

# Check if we are in the top-level project or not:
if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "${PROJECT_NAME} is a sub-project of ${CMAKE_PROJECT_NAME}\n")
else()
    message(STATUS "${CMAKE_PROJECT_NAME} is a top-level project\n")
endif()

message("\n")

# ============================================================================ #
#
#                           Configure Folders
#
# ============================================================================ #

message(STATUS "Manually setting ${PROJECT_NAME} folder structure:\n")
message("RUNTIME_OUTPUT_DIRECTORY = ${RUNTIME_OUTPUT_DIRECTORY}")
message("ARCHIVE_OUTPUT_DIRECTORY = ${ARCHIVE_OUTPUT_DIRECTORY}")
message("LIBRARY_OUTPUT_DIRECTORY = ${LIBRARY_OUTPUT_DIRECTORY}")
message("PDB_OUTPUT_DIRECTORY = ${PDB_OUTPUT_DIRECTORY}\n")

message("\n")

# ============================================================================ #
#
#                           Configure Project
#
# ============================================================================ #
