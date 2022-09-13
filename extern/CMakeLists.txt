# CMake requirements.
cmake_minimum_required(VERSION 3.7...3.24)
message("${CMAKE_CURRENT_SOURCE_DIR}/>")

find_package(Git)

# Update submodules as needed
if(GIT_FOUND)
  option(GIT_SUBMODULE "Check submodules during build" ON)
  if(GIT_SUBMODULE)
    message(STATUS "Running git submodule update --init")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
      if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "Exiting git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules!")
      else()
        message(STATUS "Completed - git submodules are up to date")
      endif()
  endif()
endif()

# This variable specifies an alternate folder containing a vcpkg.json manifest.
# Defaults to ${CMAKE_SOURCE_DIR} if ${CMAKE_SOURCE_DIR}/vcpkg.json exists.
if(DEFINED ${VCPKG_MANIFEST_DIR})
  message(STATUS "Toolchain: VCPKG_MANIFEST_DIR Using ${VCPKG_MANIFEST_DIR}")
else()
  message(STATUS "Toolchain: VCPKG_MANIFEST_DIR - Setting variable...")
  message(STATUS "Toolchain: VCPKG_MANIFEST_DIR From ${VCPKG_MANIFEST_DIR}")
  set(VCPKG_MANIFEST_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}
    CACHE STRING "vcpkg manifest file location")
  message(STATUS "Toolchain: VCPKG_MANIFEST_DIR To ${VCPKG_MANIFEST_DIR}")
endif()


if(DEFINED ${CMAKE_TOOLCHAIN_FILE})
  message(STATUS "Toolchain: Using remote vcpkg found at: ${CMAKE_TOOLCHAIN_FILE}")
else()
  message(STATUS "Toolchain: CMAKE_TOOLCHAIN_FILE not defined - Searching for submodule...")
  # This variable forces vcpkg to operate in either manifest mode or classic mode.
  # Defaults to ON when VCPKG_MANIFEST_DIR is non-empty or ${CMAKE_SOURCE_DIR}/vcpkg.json exists.
  # To disable manifest mode while a vcpkg.json is detected, set this to OFF.
  set(VCPKG_MANIFEST_MODE ON
    CACHE STRING "vcpkg manifest mode on/off")
  message(STATUS "Toolchain: VCPKG_MANIFEST_MODE = ${VCPKG_MANIFEST_MODE}")
  # This variable sets the location where libraries will be installed and consumed from.
  # In manifest mode, the default is ${CMAKE_BINARY_DIR}/vcpkg_installed.
  # In classic mode, the default is ${VCPKG_ROOT}/installed.
  set(VCPKG_INSTALLED_DIR ${CMAKE_SOURCE_DIR}/bin
    CACHE STRING "vcpkg installation directory")
  message(STATUS "Toolchain: VCPKG_INSTALLED_DIR = ${VCPKG_INSTALLED_DIR}")
  # Toolchain location. Stores result in the CMakeCache.
  set(CMAKE_TOOLCHAIN_FILE
  ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
    CACHE STRING "Toolchain file location")
  message(STATUS "Toolchain: Using local vcpkg submodule found at: ${CMAKE_TOOLCHAIN_FILE}")
endif()
