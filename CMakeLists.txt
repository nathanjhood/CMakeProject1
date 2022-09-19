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
message(STATUS "${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt>\n")

message(STATUS "Initiating CMake v${CMAKE_VERSION}\n")

message("Options:\n")
set(CMAKE_PROJECT_VENDOR "StoneyDSP")
option(USE_FOO "Use foo" OFF)
option(USE_TESTS "Use tests" ON)
option(ENABLE_LOGGING "Log cache variables to console terminal" OFF)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
option(USE_EXTERN "Use extern folder to resolve dependencies" ON)
option(GIT_SUBMODULE "Check submodules during build" ON)
option(USE_VCPKG "Use local vcpkg if found" ON)
option(ASAN_ENABLED "Build this target with AddressSanitizer" OFF)
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
  message(STATUS "${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt>\n")
endif()

# ============================================================================ #
#
#                           Create New Project
#
# ============================================================================ #

message("Detecting CMake project...")

# set project maintainer/vendor name
set(PROJECT_VENDOR ${CMAKE_PROJECT_VENDOR} CACHE STRING "Author/maintainer of this project:")

# set version using external "VERSION" file
file(READ ${CMAKE_CURRENT_LIST_DIR}/VERSION LOCAL_VERSION)
string(REGEX MATCH "VERSION_MAJOR ([0-9]*)" _ ${LOCAL_VERSION})
set(LOCAL_VERSION_MAJOR ${CMAKE_MATCH_1})
string(REGEX MATCH "VERSION_MINOR ([0-9]*)" _ ${LOCAL_VERSION})
set(LOCAL_VERSION_MINOR ${CMAKE_MATCH_1})
string(REGEX MATCH "VERSION_PATCH ([0-9]*)" _ ${LOCAL_VERSION})
set(LOCAL_VERSION_PATCH ${CMAKE_MATCH_1})
string(REGEX MATCH "VERSION_TWEAK ([0-9]*)" _ ${LOCAL_VERSION})
set(LOCAL_VERSION_TWEAK ${CMAKE_MATCH_1})
set(_ "")

# Create a CMake project here.
project (CMakeProject1
  VERSION
    ${LOCAL_VERSION_MAJOR}.${LOCAL_VERSION_MINOR}.${LOCAL_VERSION_PATCH}.${LOCAL_VERSION_TWEAK}
  DESCRIPTION
    "CMake project template with native git, vcpkg, and doxygen support."
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
set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(PDB_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

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

if(MSVC)
    # Use max Warning Level
    string(REPLACE "/W3 " "/Wall " CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    string(REPLACE "/W3 " "/Wall " CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    string(REPLACE "/W3 " "/Wall " CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
    string(REPLACE "/W3 " "/Wall " CMAKE_CXX_FLAGS_MINSIZEREL ${CMAKE_CXX_FLAGS_MINSIZEREL})
    string(REPLACE "/W3 " "/Wall " CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
    # Library needs /EHsc (Enable C++ exceptions)
endif()

message("CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
message("CMAKE_CXX_FLAGS_DEBUG = ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE = ${CMAKE_CXX_FLAGS_RELEASE}")
message("CMAKE_CXX_FLAGS_MINSIZEREL = ${CMAKE_CXX_FLAGS_MINSIZEREL}")
message("CMAKE_CXX_FLAGS_RELWITHDEBINFO = ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}\n")

message("CONFIGURATION = ${CONFIGURATION}\n")

# create config header for C++
message("Creating config header file...")
configure_file(
  ${PROJECT_SOURCE_DIR}/support/cmake/${PROJECT_NAME}Config.h.in
  ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}/${PROJECT_NAME}Config.h)
message("Created config header file.\n")

#configure_package_config_file(
#    ${PROJECT_SOURCE_DIR}/support/cmake/${PROJECT_NAME}Config.cmake.in
#    ${PROJECT_BINARY_DIR}/share/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake
#  INSTALL_DESTINATION
#    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
#)

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

  #message("Adding ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}Config.h to target ${PROJECT_NAME}-SharedCode...")
  #target_include_directories(${PROJECT_NAME}-SharedCode
  #  PUBLIC
  #    # let's include foo folder...
  #    #${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/foo
  #
  #    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/foo>
  #    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  #)
  #message("Added ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}")

  # link our imported vcpkg package library "fmt" (and others) to our shared code target...
  find_package(fmt CONFIG REQUIRED)
  target_link_libraries(${PROJECT_NAME}-SharedCode
    PUBLIC
      fmt::fmt)
  message("Linked vcpkg library fmt to target ${PROJECT_NAME}-SharedCode")

  # let's set the foo source folder as a usage requirement...
  target_include_directories(${PROJECT_NAME}-SharedCode
    INTERFACE
      ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/foo
      #<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
      #<INSTALL_INTERFACE:include>
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
add_executable (${PROJECT_NAME}-Executable)
message("Added target: ${PROJECT_NAME}-Executable.exe\n")

# Set target version.
set_target_properties(${PROJECT_NAME}-Executable
  PROPERTIES
    VERSION ${LOCAL_VERSION_MAJOR}.${LOCAL_VERSION_MINOR}.${LOCAL_VERSION_PATCH}.${LOCAL_VERSION_TWEAK})
message("Added target version ${LOCAL_VERSION_MAJOR}.${LOCAL_VERSION_MINOR}.${LOCAL_VERSION_PATCH}.${LOCAL_VERSION_TWEAK}\n")

# Add source files and headers to target.
target_sources(${PROJECT_NAME}-Executable
  PUBLIC
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/main.h
    ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}/${PROJECT_NAME}Config.h
)

# Add some headers.
message("Adding to target ${PROJECT_NAME}-Executable...\n")
#include directories for our executable program
target_include_directories(${PROJECT_NAME}-Executable
  PUBLIC
    # let's include the build tree...
    ${PROJECT_BINARY_DIR}
    # let's include the config.h...
    ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}
    # let's include main.h...
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}
)
message("Added ${PROJECT_BINARY_DIR}")
message("Added ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}")
message("Added ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}\n")

# Link any extra libraries to our "main" out...
target_link_libraries(${PROJECT_NAME}-Executable
  PUBLIC
    ${EXTRA_LIBS}
)
message("Linked EXTRA_LIBS (if any) to target ${PROJECT_NAME}-Executable\n")
message("EXTRA_LIBS = ${EXTRA_LIBS}\n")

# install the .exe
install(
  TARGETS ${PROJECT_NAME}-Executable
  DESTINATION bin
)

# install the configured c++ header (???)
#install(
#  FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h
#  DESTINATION include/${PROJECT_NAME}
#)

if(ASAN_ENABLED)
  if(MSVC)
    target_compile_options(${PROJECT_NAME}-Executable PUBLIC /fsanitize=address)
  else()
    target_compile_options(${PROJECT_NAME}-Executable PUBLIC -fsanitize=address)
    target_link_options(${PROJECT_NAME}-Executable PUBLIC -fsanitize=address)
  endif()
endif()

# ============================================================================ #
#
#                 Add tests to target: CMakeProject1-executable
#
# ============================================================================ #

if(USE_TESTS)
  message(STATUS "Testing enabled.\n")
  include(${PROJECT_SOURCE_DIR}/tests/CMakeLists.txt)
else(USE_TESTS)
  message(STATUS "Testing disabled.\n")
endif(USE_TESTS)

# ============================================================================ #
#
#                           Configure Installer
#
# ============================================================================ #

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VENDOR ${CMAKE_PROJECT_VENDOR})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_VERSION_MAJOR ${LOCAL_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${LOCAL_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${LOCAL_VERSION_PATCH})
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
message(STATUS "Include (CPack)\n")

message("CPACK_PACKAGE_VENDOR = ${CPACK_PACKAGE_VENDOR}")
message("CPACK_PACKAGE_DESCRIPTION_SUMMARY = ${PROJECT_DESCRIPTION}")
message("CPACK_PACKAGE_VERSION_MAJOR = ${LOCAL_VERSION_MAJOR}")
message("CPACK_PACKAGE_VERSION_MINOR = ${LOCAL_VERSION_MINOR}")
message("CPACK_PACKAGE_VERSION_PATCH = ${LOCAL_VERSION_PATCH}")
message("CPACK_RESOURCE_FILE_LICENSE = ${CMAKE_CURRENT_LIST_DIR}/LICENCE")
message("CPACK_RESOURCE_FILE_README = ${CMAKE_CURRENT_LIST_DIR}/README.md")
message("CPACK_SOURCE_GENERATOR = ${CPACK_SOURCE_GENERATOR}")
message("CPack ignores: ${CPACK_SOURCE_IGNORE_FILES}\n")
