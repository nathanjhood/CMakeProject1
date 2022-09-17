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

# Fallback for using newer policies on CMake <3.12.
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

message("\n")
message(STATUS "${CMAKE_CURRENT_LIST_DIR}/>\n")

message(STATUS "Initiating CMake v${CMAKE_VERSION}\n")

message("Options:\n")
set(CMAKE_PROJECT_VENDOR "StoneyDSP")
option(USE_FOO "Use foo" ON)
option(USE_TESTS "Use tests" ON)
option(ENABLE_LOGGING "Log cache variables to console terminal" OFF)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
option(USE_EXTERN "Use extern folder to resolve dependencies" ON)
option(GIT_SUBMODULE "Check submodules during build" ON)
option(USE_VCPKG "Use local vcpkg if found" ON)
set_property(GLOBAL PROPERTY USE_FOLDERS YES)

message("USE_FOO = ${USE_FOO}")
message("USE_TESTS = ${USE_TESTS}")
message("CMAKE_PROJECT_VENDOR = ${CMAKE_PROJECT_VENDOR}")
message("ENABLE_LOGGING = ${ENABLE_LOGGING}")
message("BUILD_SHARED_LIBS = ${BUILD_SHARED_LIBS}")
message("USE_EXTERN = ${USE_EXTERN}")
message("GIT_SUBMODULE = ${GIT_SUBMODULE}")
message("USE_VCPKG = ${USE_VCPKG}")
message("USE_FOLDERS = ${USE_FOLDERS}\n")

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

set(PROJECT_VENDOR ${CMAKE_PROJECT_VENDOR} CACHE STRING "Author/maintainer of this project:")

# Create a CMake project here.
project (CMakeProject1
  VERSION
    1.0.0.0
  DESCRIPTION
    "VS Console Application with CMake, vcpkg, Doxygen, and JUCE support"
  HOMEPAGE_URL
    https://github.com/${PROJECT_VENDOR}/CMakeProject1
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
message("by ${PROJECT_VENDOR}\n")

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

# get access to helper functions for creating config files
include(CMakePackageConfigHelpers)

# make cache variables for install destinations
include(GNUInstallDirs)

# Configure folder structure.
set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(PDB_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
#set(CMAKE_CFG_INTDIR ${PROJECT_BINARY_DIR}/artefacts)

message(STATUS "Manually setting ${PROJECT_NAME} folder structure:\n")
message("RUNTIME_OUTPUT_DIRECTORY = ${RUNTIME_OUTPUT_DIRECTORY}")
message("ARCHIVE_OUTPUT_DIRECTORY = ${ARCHIVE_OUTPUT_DIRECTORY}")
message("LIBRARY_OUTPUT_DIRECTORY = ${LIBRARY_OUTPUT_DIRECTORY}")
message("PDB_OUTPUT_DIRECTORY = ${PDB_OUTPUT_DIRECTORY}")
message("CMAKE_CFG_INTDIR = ${CMAKE_CFG_INTDIR}\n")

# ============================================================================ #
#
#                           Configure Project
#
# ============================================================================ #

# create config header for C++
message("Creating config header file...")
configure_file(
  ${PROJECT_SOURCE_DIR}/support/cmake/${PROJECT_NAME}Config.h.in
  ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}/cfg/${PROJECT_NAME}Config.h)
message("Created config header file.\n")

    ${PROJECT_SOURCE_DIR}/support/cmake/${PROJECT_NAME}Config.cmake.in
# ============================================================================ #
#
#                    Add target: CMakeProject1-library
#
# ============================================================================ #

if(USE_FOO)
  # Add output target.
  message("Adding target...")
  add_library (${PROJECT_NAME}-SharedCode
    STATIC
      ${PROJECT_SOURCE_DIR}/src/foo/foo.cpp)
  message("Added target: ${PROJECT_NAME}-SharedCode.lib\n")

  message("Adding ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}Config.h to target ${PROJECT_NAME}-SharedCode...")
  target_include_directories(${PROJECT_NAME}-SharedCode
    PUBLIC
      # let's include foo folder...
      ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/foo
  )
  message("Added ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}")

  # link our imported vcpkg package library "fmt" (and others) to our shared code target...
  find_package(fmt CONFIG REQUIRED)
  target_link_libraries(${PROJECT_NAME}-SharedCode
    PUBLIC
      fmt::fmt
  )
  message("Linked vcpkg library fmt to target ${PROJECT_NAME}-SharedCode")

  # let's set the foo source folder as a usage requirement...
  target_include_directories(${PROJECT_NAME}-SharedCode
    INTERFACE
      ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/foo
  )

  # install the definition-containing library (.lib)
  install(
    TARGETS ${PROJECT_NAME}-SharedCode
    DESTINATION lib
  )

  # install the declaration-containing header (.h)
  install(
    FILES ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/foo/foo.h
    DESTINATION include/${PROJECT_NAME}/foo
  )

  list(APPEND EXTRA_LIBS ${PROJECT_NAME}-SharedCode)
endif(USE_FOO)

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

#include directories for our executable program
target_include_directories(${PROJECT_NAME}-Executable
  PUBLIC
    # let's include the config.h...
    ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}/cfg
    # let's include main.h...
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}
)
message("Added ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}")

# Link our function library to our "main" out...
target_link_libraries(${PROJECT_NAME}-Executable
  PUBLIC
    ${EXTRA_LIBS}
)
message("Linked library ${PROJECT_NAME}-SharedCode to target ${PROJECT_NAME}-Executable")

# install the definition-containing .exe
install(
  TARGETS ${PROJECT_NAME}-Executable
  DESTINATION bin)

# install the configured c++ header
install(
  FILES ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}/cfg/${PROJECT_NAME}Config.h
  DESTINATION include/${PROJECT_NAME}/cfg
)

# ============================================================================ #
#
#                 Add tests to target: CMakeProject1-executable
#
# ============================================================================ #

if(USE_TESTS)
  message(STATUS "Testing enabled.")
  include(${PROJECT_SOURCE_DIR}/tests/CMakeLists.txt)
else(USE_TESTS)
  message(STATUS "Testing disabled.")
endif(USE_TESTS)

# ============================================================================ #
#
#                           Configure Installer
#
# ============================================================================ #

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VENDOR ${CMAKE_PROJECT_VENDOR})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_LIST_DIR}/LICENCE)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_LIST_DIR}/README.md)
set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
set(CPACK_SOURCE_IGNORE_FILES
    /.git
    /.github
    /.vs
    /.vscode
    /bin
    /installed
    /.*build.*
    /\\\\.DS_Store
)

# include installer generator
include(CPack)
message(STATUS "Include (CPack)")

message("CPACK_PACKAGE_VENDOR = ${CPACK_PACKAGE_VENDOR}")
message(STATUS "CPack generators: ${CPACK_SOURCE_GENERATOR}")
message(STATUS "CPack ignores: ${CPACK_SOURCE_IGNORE_FILES}")
