# ============================================================================ #
#
# @file main.cpp
#
# @author Nathan J. Hood ( @StoneyDSP )
# @brief Defines the main execution routine of the application.
# @version 1.0.0.0
# @date 2022-08-23
#
# @copyright Copyright (c) 2022
#
# ============================================================================ #

# ============================================================================ #
#
#                             Configure CMake
#
# ============================================================================ #

# Top-level CMake project file, do global configuration
# and include sub-projects here.

# CMake requirements.
cmake_minimum_required(VERSION 3.7...3.24.2)

# CMake policy.
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

message("\n")
message(STATUS "${CMAKE_CURRENT_LIST_DIR}/>\n")

message(STATUS "Initiating CMake v${CMAKE_VERSION}\n")

message("Options:\n")
option(ENABLE_LOGGING "Log cache variables to console terminal" OFF)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
option(USE_EXTERN "Use extern folder to resolve dependencies" ON)
option(GIT_SUBMODULE "Check submodules during build" ON)
option(USE_VCPKG "Use local vcpkg if found" ON)
set_property(GLOBAL PROPERTY USE_FOLDERS YES)

message("ENABLE_LOGGING = ${ENABLE_LOGGING}")
message("BUILD_SHARED_LIBS = ${BUILD_SHARED_LIBS}")
message("USE_EXTERN = ${USE_EXTERN}")
message("GIT_SUBMODULE = ${GIT_SUBMODULE}")
message("USE_VCPKG = ${USE_VCPKG}")
message("USE_FOLDERS = ${USE_FOLDERS}")
message("\n")

# ============================================================================ #
#
#                           Configure Dependencies
#
# ============================================================================ #

if(USE_EXTERN)
  # add required packages
  message(STATUS "Checking git...\n")
  if(GIT_FOUND)
    message("git: already found. Using: ${CMAKE_PROJECT_NAME} submodules")
  else()
    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/.gitmodules)
      message("git: adding local submodules...")
      include(extern/CMakeLists.txt)
    else()
      message("git: no submodule file found")
    endif()
  endif()
endif()

# ============================================================================ #
#
#                           Create New Project
#
# ============================================================================ #

message(STATUS "${CMAKE_CURRENT_LIST_DIR}/>\n")

message("Detecting CMake project...")

set(PROJECT_AUTHOR "StoneyDSP" CACHE STRING "Author/maintainer of this project:")

# Create a CMake project here.
project (CMakeProject1
  VERSION
    1.0.0.0
  DESCRIPTION
    "VS Console Application with CMake, vcpkg, Doxygen, and JUCE support"
  HOMEPAGE_URL
    https://github.com/${PROJECT_AUTHOR}/CMakeProject1
  LANGUAGES
    C CXX
)

# specify the C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "...Detected project:\n")
message("${PROJECT_NAME} v${PROJECT_VERSION}")
message("${PROJECT_DESCRIPTION}")
message("${PROJECT_HOMEPAGE_URL}")
message("by ${PROJECT_AUTHOR}\n")

# Check if we are in the top-level project or not:
if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "${PROJECT_NAME} is a sub-project of ${CMAKE_PROJECT_NAME}")
else()
    message(STATUS "${CMAKE_PROJECT_NAME} is a top-level project")
endif()

# ============================================================================ #
#
#                           Configure Folders
#
# ============================================================================ #

# Configure folder structure.
#set(PROJECT_BINARY_DIR ${CMAKE_CURRENT_LIST_DIR}/bin)
#set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(PDB_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_INTDIR ${PROJECT_BINARY_DIR}/artefacts)

message(STATUS "Manually setting ${PROJECT_NAME} folder structure:\n")
message("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message("PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")
message("RUNTIME_OUTPUT_DIRECTORY = ${RUNTIME_OUTPUT_DIRECTORY}")
message("ARCHIVE_OUTPUT_DIRECTORY = ${ARCHIVE_OUTPUT_DIRECTORY}")
message("LIBRARY_OUTPUT_DIRECTORY = ${LIBRARY_OUTPUT_DIRECTORY}")
message("PDB_OUTPUT_DIRECTORY = ${PDB_OUTPUT_DIRECTORY}")
message("CMAKE_INTDIR = ${CMAKE_INTDIR}\n")

# ============================================================================ #
#
#                           Configure Project
#
# ============================================================================ #

# create config header for C++
message("Creating config header file...")
configure_file(
  ${PROJECT_SOURCE_DIR}/support/cmake/${PROJECT_NAME}Config.h.in
  ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}/${PROJECT_NAME}Config.h)
message("Created config header file.\n")

# ============================================================================ #
#
#                    Add target: CMakeProject1-library
#
# ============================================================================ #

# Add output target.
message("Adding target...")
add_library (${PROJECT_NAME}-SharedCode
  STATIC
    ${PROJECT_SOURCE_DIR}/src/foo.cpp)
message("Added target: ${PROJECT_NAME}-SharedCode.lib\n")

#message("Adding ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}Config.h to target ${PROJECT_NAME}-SharedCode...")
target_include_directories(${PROJECT_NAME}-SharedCode
  PUBLIC
    # let's include the config.h...
    ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}
    # let's include main.h...
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}
)
message("Added ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}")

# ============================================================================ #
#
#                    Add target: CMakeProject1-executable
#
# ============================================================================ #

# Add output target.
message("Adding target...")
add_executable (${PROJECT_NAME}-Executable
    ${PROJECT_SOURCE_DIR}/src/main.cpp)
message("Added target: ${PROJECT_NAME}-Executable.exe\n")

# Add some headers.
message("Adding ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}Config.h to target ${PROJECT_NAME}-Executable...")
target_include_directories(${PROJECT_NAME}-Executable
  PUBLIC
    # let's include the config.h...
    ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}
    # let's include main.h...
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}
)
message("Added ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}")

message("Linking library ${PROJECT_NAME}-SharedCode to target ${PROJECT_NAME}-Executable")
target_link_libraries(${PROJECT_NAME}-Executable PUBLIC ${PROJECT_NAME}-SharedCode)
