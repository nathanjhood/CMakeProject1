# ============================================================================ #
#
# @file CMakeLists.txt
#
# @author Nathan J. Hood ( @StoneyDSP )
# @brief Defines the main configuration routine of the top-level project.
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
#                           Configure Submodules
#
# ============================================================================ #

message("\n")
message(STATUS "${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt>\n")

find_package(Git)

# Update submodules as needed
if(GIT_FOUND)
  #option(GIT_SUBMODULE "Check submodules during build" ON)
  if(GIT_SUBMODULE)
    message(STATUS "Running git submodule update --init")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
      if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "Running git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules!\n")
      else()
        message(STATUS "Running git submodule update --init complete; all git submodules are up to date.\n")
      endif()
  endif(GIT_SUBMODULE)
else(GIT_FOUND)
  message(FATAL_ERROR "Running git submodule update --init failed; git not found!\n")
endif(GIT_FOUND)

message("\n")

# ============================================================================ #
#
#                               Configure vcpkg
#
# ============================================================================ #

# This variable specifies an alternate folder containing a vcpkg.json manifest.
# Defaults to ${CMAKE_SOURCE_DIR} if ${CMAKE_SOURCE_DIR}/vcpkg.json exists.
if(DEFINED ${VCPKG_MANIFEST_DIR})
  message(STATUS "vcpkg.json detected...\n")
  message("Toolchain: VCPKG_MANIFEST_DIR = ${VCPKG_MANIFEST_DIR}")
else(DEFINED ${VCPKG_MANIFEST_DIR})
  set(VCPKG_MANIFEST_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/extern
    CACHE STRING "vcpkg manifest file location")
  message("Toolchain: VCPKG_MANIFEST_DIR = ${VCPKG_MANIFEST_DIR}")
endif(DEFINED ${VCPKG_MANIFEST_DIR})

if(USE_VCPKG)
  if(DEFINED ${CMAKE_TOOLCHAIN_FILE})
    message("Toolchain: Using remote vcpkg found at: ${CMAKE_TOOLCHAIN_FILE}")
  else(DEFINED ${CMAKE_TOOLCHAIN_FILE})
    message("Toolchain: CMAKE_TOOLCHAIN_FILE not defined - Searching for submodule...")
    option(VCPKG_VERBOSE "verbose vcpkg output logging" ON)
    # This variable forces vcpkg to operate in either manifest mode or classic mode.
    # Defaults to ON when VCPKG_MANIFEST_DIR is non-empty or ${CMAKE_SOURCE_DIR}/vcpkg.json exists.
    # To disable manifest mode while a vcpkg.json is detected, set this to OFF.
    set(VCPKG_MANIFEST_MODE ON
      CACHE STRING "vcpkg manifest mode on/off")
    message("Toolchain: VCPKG_MANIFEST_MODE = ${VCPKG_MANIFEST_MODE}")
    # This environment variable can be set to an existing directory to use for
    # storing downloads instead of the internal downloads/ directory.
    # It should always be set to an absolute path.
    set(VCPKG_DOWNLOADS ${CMAKE_CURRENT_SOURCE_DIR}/downloads
      CACHE STRING "vcpkg package downloads directory")
    message("Toolchain: VCPKG_DOWNLOADS = ${VCPKG_DOWNLOADS}")
    # This variable sets the location where libraries will be installed and consumed from.
    # In manifest mode, the default is ${CMAKE_BINARY_DIR}/vcpkg_installed.
    # In classic mode, the default is ${VCPKG_ROOT}/installed.
    set(VCPKG_INSTALLED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/installed
      CACHE STRING "vcpkg package installation directory")
    message("Toolchain: VCPKG_INSTALLED_DIR = ${VCPKG_INSTALLED_DIR}")
    # location of .vcpkg-root file
    set(VCPKG_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/extern/vcpkg
      CACHE STRING "location of .vcpkg-root file")
    message("Toolchain: VCPKG_ROOT = ${VCPKG_ROOT}")
    # define vcpkg required feature flags
    set(VCPKG_FEATURE_FLAGS "manifests,versions,binarycaching,registries")
    message("Toolchain: VCPKG_FEATURE_FLAGS = ${VCPKG_FEATURE_FLAGS}")
    # Toolchain location. Stores result in the CMakeCache.
    set(CMAKE_TOOLCHAIN_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/extern/vcpkg/scripts/buildsystems/vcpkg.cmake
      CACHE STRING "Toolchain file location")
    message("Toolchain: Using local vcpkg submodule found at: ${CMAKE_TOOLCHAIN_FILE}\n")
  endif(DEFINED ${CMAKE_TOOLCHAIN_FILE})
endif(USE_VCPKG)

#vcpkg_cmake_get_vars(CMAKE_VARS_FILE)
#include(${CMAKE_VARS_FILE})
#message(STATUS "detected CXX flags: ${VCPKG_DETECTED_CMAKE_CXX_FLAGS}\n")

message("CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
message("CMAKE_CXX_FLAGS_DEBUG = ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE = ${CMAKE_CXX_FLAGS_RELEASE}")
message("CMAKE_CXX_FLAGS_MINSIZEREL = ${CMAKE_CXX_FLAGS_MINSIZEREL}")
message("CMAKE_CXX_FLAGS_RELWITHDEBINFO = ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}\n")

message("CMAKE_C_FLAGS = ${CMAKE_C_FLAGS}")
message("CMAKE_C_FLAGS_DEBUG = ${CMAKE_C_FLAGS_DEBUG}")
message("CMAKE_C_FLAGS_RELEASE = ${CMAKE_C_FLAGS_RELEASE}")
message("CMAKE_C_FLAGS_MINSIZEREL = ${CMAKE_C_FLAGS_MINSIZEREL}")
message("CMAKE_C_FLAGS_RELWITHDEBINFO = ${CMAKE_C_FLAGS_RELWITHDEBINFO}\n")

if(USE_VCPKG)
  set(VCPKG_CXX_FLAGS ${CMAKE_CXX_FLAGS})
  set(VCPKG_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
  set(VCPKG_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
  set(VCPKG_CXX_FLAGS_MINSIZEREL ${CMAKE_CXX_FLAGS_MINSIZEREL})
  set(VCPKG_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})

  set(VCPKG_C_FLAGS ${CMAKE_C_FLAGS})
  set(VCPKG_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
  set(VCPKG_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})
  set(VCPKG_C_FLAGS_MINSIZEREL ${CMAKE_C_FLAGS_MINSIZEREL})
  set(VCPKG_C_FLAGS_RELWITHDEBINFO ${CMAKE_C_FLAGS_RELWITHDEBINFO})
endif(USE_VCPKG)

message("VCPKG_CXX_FLAGS = ${VCPKG_CXX_FLAGS}")
message("VCPKG_CXX_FLAGS_DEBUG = ${VCPKG_CXX_FLAGS_DEBUG}")
message("VCPKG_CXX_FLAGS_RELEASE = ${VCPKG_CXX_FLAGS_RELEASE}")
message("VCPKG_CXX_FLAGS_MINSIZEREL = ${VCPKG_CXX_FLAGS_MINSIZEREL}")
message("VCPKG_CXX_FLAGS_RELWITHDEBINFO = ${VCPKG_CXX_FLAGS_RELWITHDEBINFO}\n")

message("VCPKG_C_FLAGS = ${VCPKG_C_FLAGS}")
message("VCPKG_C_FLAGS_DEBUG = ${VCPKG_C_FLAGS_DEBUG}")
message("VCPKG_C_FLAGS_RELEASE = ${VCPKG_C_FLAGS_RELEASE}")
message("VCPKG_C_FLAGS_MINSIZEREL = ${VCPKG_C_FLAGS_MINSIZEREL}")
message("VCPKG_C_FLAGS_RELWITHDEBINFO = ${VCPKG_C_FLAGS_RELWITHDEBINFO}\n")

message("\n")
