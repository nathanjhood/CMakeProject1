# ============================================================================ #
#
# @file CMakeLists.txt [Root] - CMakeProject1
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

# Fallback for using newer policies on CMake <3.12.
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

message("\n")

# ============================================================================ #
#
#                             Configure CMake
#
# ============================================================================ #

# Top-level CMake project file, do global configuration
# and include sub-projects here.

# PROJECT_IS_TOP_LEVEL determines whether the project is being used from root
# or if it is added as a dependency (through add_subdirectory for example).
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(PROJECT_IS_TOP_LEVEL TRUE)
  message(STATUS "CMake found at: ${CMAKE_COMMAND}\n")
  message(STATUS "Initiating CMake v${CMAKE_VERSION}\n")
else()
  set(PROJECT_IS_TOP_LEVEL FALSE)
  message(STATUS "${CMAKE_PROJECT_NAME} is the top-level project\n")
endif ()

message(STATUS "Detecting Compiler...\n")
message("CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER})
message("CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER})
 #include(${CMAKE_CURRENT_LIST_DIR}/extern/vcpkg/scripts/detect_compiler/CMakeLists.txt)
message(STATUS "Compiler detected.\n")

# if(DEFINED CMAKE_CXX_COMPILER)
#     message("CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER})
#   message(STATUS "Detecting Compiler...\n")
#   include(${CMAKE_CURRENT_LIST_DIR}/extern/vcpkg/scripts/detect_compiler/CMakeLists.txt)
#   message(STATUS "Compiler detected.\n")

    # message("CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})
    # message("CMAKE_CXX_FLAGS_DEBUG: " ${CMAKE_CXX_FLAGS_DEBUG})
    # message("CMAKE_CXX_FLAGS_RELEASE: " ${CMAKE_CXX_FLAGS_RELEASE})
    # message("CMAKE_CXX_FLAGS_MINSIZEREL: " ${CMAKE_CXX_FLAGS_MINSIZEREL})
    # message("CMAKE_CXX_FLAGS_RELWITHDEBINFO: " ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})

    # message("CMAKE_C_FLAGS = ${CMAKE_C_FLAGS}")
    # message("CMAKE_C_FLAGS_DEBUG = ${CMAKE_C_FLAGS_DEBUG}")
    # message("CMAKE_C_FLAGS_RELEASE = ${CMAKE_C_FLAGS_RELEASE}")
    # message("CMAKE_C_FLAGS_MINSIZEREL = ${CMAKE_C_FLAGS_MINSIZEREL}")
    # message("CMAKE_C_FLAGS_RELWITHDEBINFO = ${CMAKE_C_FLAGS_RELWITHDEBINFO}\n")
# endif()

# Ensure a valid build type is set
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    if(PROJECT_IS_TOP_LEVEL)
        set(DEFAULT_BUILD_TYPE Debug)
    else()
        message(WARNING "Default build type is not set (CMAKE_BUILD_TYPE)")
    endif()
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Print the flags for the user
if (DEFINED CMAKE_BUILD_TYPE)
    message(STATUS "Generated build type: ${CMAKE_BUILD_TYPE}")
else ()
    message(STATUS "Generated config types: ${CMAKE_CONFIGURATION_TYPES}")
endif ()

# We can define some useful options (such as enabling terminal logging) and set defaults here...
option(LOGGING "Log to terminal" ON)
# Set project author/vendor name variable
set(CMAKE_PROJECT_VENDOR "StoneyDSP")
# Get the list of ignored files from .gitignore
set(GIT_IGNORE ${PROJECT_SOURCE_DIR}/.gitignore)
# Use extern folder to resolve dependencies
option(USE_EXTERN "Use extern folder to resolve dependencies" ON)
# Check submodules during build
option(GIT_SUBMODULE "Check submodules during build" ON)
# Use local vcpkg if found
option(USE_VCPKG "Use local vcpkg if found" ON)
# Use "foo" example library
option(USE_FOO "Use 'foo' example library" ON)
# Use tests
option(USE_TESTS "Use tests" ON)
# Build using shared libraries. if this is set to ON, then all libraries are built as shared libraries by default.
option(BUILD_SHARED_LIBS "Build using shared libraries." ON)
# option for outputting compiler information at runtime
option(OUTPUT_COMPILER_INFO "Output compiler information when launching the main executable." ON)
# Build with Address Sanitizer
option(ASAN_ENABLED "Build with Address Sanitizer" OFF)
# Use the target 'FOLDER' property to organize targets into folders
set(USE_FOLDERS OFF)
# export symbols on Windows for shared libraries to work
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# https://stackoverflow.com/questions/48580399/how-to-ensure-a-generated-config-h-file-is-in-the-include-path
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Use external version file (could be optional?)
include(${CMAKE_CURRENT_LIST_DIR}/support/cmake/version-handling.cmake)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(USE_X64 TRUE)
else()
  set(USE_X64 FALSE)
endif()

set(CMAKE_MODULE_PATH
  "${CMAKE_MODULE_PATH}"
  "${CMAKE_CURRENT_SOURCE_DIR}/support/cmake"
  "${CMAKE_CURRENT_SOURCE_DIR}/extern/vcpkg/scripts/ports.cmake")

if(LOGGING)
  message("Options:\n")
  message("CMAKE_PROJECT_VENDOR = " ${CMAKE_PROJECT_VENDOR})
  message("USE_EXTERN = " ${USE_EXTERN})
  message("GIT_SUBMODULE = " ${GIT_SUBMODULE})
  message("USE_VCPKG = " ${USE_VCPKG})
  message("USE_FOO = " ${USE_FOO})
  message("USE_TESTS = " ${USE_TESTS})
  message("BUILD_SHARED_LIBS = " ${BUILD_SHARED_LIBS})
  message("ASAN_ENABLED = " ${ASAN_ENABLED})
  message("CMAKE_INCLUDE_CURRENT_DIR = " ${CMAKE_INCLUDE_CURRENT_DIR})
endif(LOGGING)

message("\n")

# ============================================================================ #
#
#                           Configure Dependencies
#
# ============================================================================ #

if(USE_EXTERN)
  # add required packages
  message(STATUS "Checking git...\n")
  message("\n")

  if(GIT_FOUND)
    message("git: already found. Using: ${CMAKE_PROJECT_NAME} submodules\n")
  else()
    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/.gitmodules)
      message("git: adding local submodules...\n")
      find_package(Git)

      # Update submodules as needed
      if(GIT_FOUND)

        if(GIT_SUBMODULE)
          message(STATUS "Running git submodule update --init")
          execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init
                          WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
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

    else()
      message("git: no submodule file found\n")
    endif()

  endif()

endif()

message("\n")

# ============================================================================ #
#
#                               Configure vcpkg
#
# ============================================================================ #

if(USE_VCPKG)
  file(COPY ${CMAKE_CURRENT_LIST_DIR}/support/msbuild/Directory.Build.props DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  file(COPY ${CMAKE_CURRENT_LIST_DIR}/support/msbuild/Directory.Build.targets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  file(COPY ${CMAKE_CURRENT_LIST_DIR}/extern/vcpkg/scripts/buildsystems/msbuild/vcpkg.props DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/extern/vcpkg/scripts/buildsystems/msbuild)
  file(COPY ${CMAKE_CURRENT_LIST_DIR}/extern/vcpkg/scripts/buildsystems/msbuild/vcpkg.targets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/extern/vcpkg/scripts/buildsystems/msbuild)
  file(COPY ${CMAKE_CURRENT_LIST_DIR}/extern/vcpkg/scripts/buildsystems/msbuild/vcpkg-general.xml DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/extern/vcpkg/scripts/buildsystems/msbuild)
  file(COPY ${CMAKE_CURRENT_LIST_DIR}/extern/vcpkg/scripts/buildsystems/msbuild/applocal.ps1 DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/extern/vcpkg/scripts/buildsystems/msbuild)
  file(COPY ${CMAKE_CURRENT_LIST_DIR}/extern/vcpkg/scripts/buildsystems/vcpkg.cmake DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/extern/vcpkg/scripts/buildsystems)

  #include(${CMAKE_CURRENT_SOURCE_DIR}/extern/vcpkg/scripts/get_cmake_vars/CMakeLists.txt)

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

  if(LOGGING)
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
  endif()

  # This variable specifies an alternate folder containing a vcpkg.json manifest.
  # Defaults to ${CMAKE_SOURCE_DIR} if ${CMAKE_SOURCE_DIR}/vcpkg.json exists.
  if(DEFINED ${VCPKG_MANIFEST_DIR})
    message(STATUS "vcpkg.json detected...\n")
    message("Toolchain: VCPKG_MANIFEST_DIR = ${VCPKG_MANIFEST_DIR}")
  else()
    set(VCPKG_MANIFEST_DIR
    ${CMAKE_CURRENT_LIST_DIR}/extern
      CACHE STRING "vcpkg manifest file location")
    message("Toolchain: VCPKG_MANIFEST_DIR = ${VCPKG_MANIFEST_DIR}")
  endif()

  if(DEFINED ${CMAKE_TOOLCHAIN_FILE})
    message("Toolchain: Using remote vcpkg found at: ${CMAKE_TOOLCHAIN_FILE}")
  else(DEFINED ${CMAKE_TOOLCHAIN_FILE})
    message("Toolchain: CMAKE_TOOLCHAIN_FILE not defined - Searching for submodule...")

    # Verbose vcpkg output logging
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
    set(VCPKG_DOWNLOADS ${CMAKE_CURRENT_LIST_DIR}/downloads
      CACHE STRING "vcpkg package downloads directory")
    message("Toolchain: VCPKG_DOWNLOADS = ${VCPKG_DOWNLOADS}")

    # This variable sets the location where libraries will be installed and consumed from.
    # In manifest mode, the default is ${CMAKE_BINARY_DIR}/vcpkg_installed.
    # In classic mode, the default is ${VCPKG_ROOT}/installed.
    set(VCPKG_INSTALLED_DIR ${CMAKE_CURRENT_LIST_DIR}/installed
      CACHE STRING "vcpkg package installation directory")
    message("Toolchain: VCPKG_INSTALLED_DIR = ${VCPKG_INSTALLED_DIR}")

    # location of .vcpkg-root file
    set(VCPKG_ROOT ${CMAKE_CURRENT_LIST_DIR}/extern/vcpkg
      CACHE STRING "location of .vcpkg-root file")
    message("Toolchain: VCPKG_ROOT = ${VCPKG_ROOT}")

    # define vcpkg required feature flags
    set(VCPKG_FEATURE_FLAGS "manifests,versions,binarycaching,registries")
    message("Toolchain: VCPKG_FEATURE_FLAGS = ${VCPKG_FEATURE_FLAGS}")

    # Toolchain location. Stores result in the CMakeCache.
    set(CMAKE_TOOLCHAIN_FILE
    ${CMAKE_CURRENT_LIST_DIR}/extern/vcpkg/scripts/buildsystems/vcpkg.cmake
      CACHE STRING "Toolchain file location")
    message("Toolchain: Using local vcpkg submodule found at: ${CMAKE_TOOLCHAIN_FILE}\n")

  endif(DEFINED ${CMAKE_TOOLCHAIN_FILE})

  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${VCPKG_ROOT}/scripts)

  #include(${CMAKE_INSTALL_PREFIX}/share/vcpkg-cmake/vcpkg-port-config.cmake)
  #include(${CMAKE_INSTALL_PREFIX}/share/vcpkg-cmake-config/vcpkg-port-config.cmake)
  #include(${CMAKE_INSTALL_PREFIX}/share/vcpkg-cmake-get-vars/vcpkg-port-config.cmake)

  #vcpkg_cmake_get_vars(CMAKE_VARS_FILE)
  #include(${CMAKE_VARS_FILE})
  #message(STATUS "detected CXX flags: ${VCPKG_DETECTED_CMAKE_CXX_FLAGS}\n")

endif(USE_VCPKG)

message("\n")

# ============================================================================ #
#
#                           Create New Project
#
# ============================================================================ #

message(STATUS "Detecting CMake project...\n")

# Create a CMake project here.
project (CMakeProject1
  VERSION
    ${LOCAL_VERSION_MAJOR}.${LOCAL_VERSION_MINOR}.${LOCAL_VERSION_PATCH}.${LOCAL_VERSION_TWEAK}
  DESCRIPTION
    "CMake project template for multi-platform continuous-integration pipelines, with native extensible build, test, debug, install workflows and git, vcpkg, and 3rd-party module support."
  HOMEPAGE_URL
    https://github.com/${PROJECT_VENDOR}/CMakeProject1
  LANGUAGES
    C CXX
)

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)

# set project maintainer/vendor name
set(PROJECT_VENDOR ${CMAKE_PROJECT_VENDOR} CACHE STRING "Author/maintainer of this project:")

# specify the C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

# specify the C++ standard
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set(CMAKE_CXX_STANDARD 20)
else()
  set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(LOGGING)
  message(STATUS "...Detected project:\n")
  message("${PROJECT_NAME} v${PROJECT_VERSION}")
  message("${PROJECT_DESCRIPTION}")
  message("${PROJECT_HOMEPAGE_URL}")
  message("@ ${PROJECT_VENDOR}\n")
endif()

# Check if we are in the top-level project or not:
if (NOT PROJECT_IS_TOP_LEVEL)
    message(STATUS "${PROJECT_NAME} is a sub-project of ${CMAKE_PROJECT_NAME}\n")
else()
    message(STATUS "${CMAKE_PROJECT_NAME} is a top-level project\n")
endif()

message("\n")

# ============================================================================ #
#
#                           Configure Installer
#
# ============================================================================ #

message(STATUS "Configuring CPack installer...\n")

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
    /.git/*
    /.github
    /.vs
    /.vscode
    /build
    /downloads
    /installed
    /vcpkg
    /.*build.*
    /\\\\.DS_Store
)

if(LOGGING)
  message("CPACK_PACKAGE_VENDOR = ${CPACK_PACKAGE_VENDOR}")
  message("CPACK_PACKAGE_DESCRIPTION_SUMMARY = ${PROJECT_DESCRIPTION}")
  message("CPACK_PACKAGE_VERSION_MAJOR = ${LOCAL_VERSION_MAJOR}")
  message("CPACK_PACKAGE_VERSION_MINOR = ${LOCAL_VERSION_MINOR}")
  message("CPACK_PACKAGE_VERSION_PATCH = ${LOCAL_VERSION_PATCH}")
  message("CPACK_RESOURCE_FILE_LICENSE = ${CMAKE_CURRENT_LIST_DIR}/LICENCE")
  message("CPACK_RESOURCE_FILE_README = ${CMAKE_CURRENT_LIST_DIR}/README.md")
  message("CPACK_SOURCE_GENERATOR = ${CPACK_SOURCE_GENERATOR}")
  message("CPack ignores: ${CPACK_SOURCE_IGNORE_FILES}\n")
endif()

# include installer generator
include(CPack)

# make cache variables for install destinations
include(GNUInstallDirs)

message("\n")

# ============================================================================ #
#
#                           Configure Project
#
# ============================================================================ #

# get access to helper functions for creating config files
include(CMakePackageConfigHelpers)

# Configure folder structure.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib                       CACHE PATH "Archive output dir.")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib                       CACHE PATH "Library output dir.")
set(CMAKE_PDB_OUTPUT_DIRECTORY      ${CMAKE_BINARY_DIR}/bin                       CACHE PATH "PDB (MSVC debug symbol)output dir.")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin                       CACHE PATH "Executable/dll output dir.")
set(${PROJECT_NAME}_INC_DIR         ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}   CACHE PATH "Installation directory for include files, a relative path that will be joined with ${CMAKE_INSTALL_PREFIX} or an absolute path.")
set(${PROJECT_NAME}_LIB_DIR         ${CMAKE_INSTALL_LIBDIR}                       CACHE PATH "Installation directory for libraries, a relative path that will be joined to ${CMAKE_INSTALL_PREFIX} or an absolute path.")
set(${PROJECT_NAME}_CMAKE_DIR       ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME} CACHE PATH "Installation directory for CMake (.cmake) files, a relative path that will be joined with ${CMAKE_INSTALL_PREFIX} or an absolute path.")
set(${PROJECT_NAME}_PKGCONFIG_DIR   ${CMAKE_INSTALL_LIBDIR}/pkgconfig             CACHE PATH "Installation directory for pkgconfig (.pc) files, a relative path that will be joined with ${CMAKE_INSTALL_PREFIX} or an absolute path.")

# Configure files.
set(VERSION_CONFIG                  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake)
set(PROJECT_CONFIG                  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake)
set(CM_VARS_CONFIG                  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h)
set(PACKAGE_CONFIG                  ${PROJECT_BINARY_DIR}/${PROJECT_NAME_LOWER}.pc)
set(VCPKG_MNFST                     ${PROJECT_BINARY_DIR}/vcpkg.json)
set(VCPKG_CONFIG                    ${PROJECT_BINARY_DIR}/vcpkg-configuration.json)
set(PORT_FILE                       ${PROJECT_BINARY_DIR}/${PROJECT_NAME_LOWER}-portfile.cmake)
set(TARGETS_EXPORT_NAME             ${PROJECT_NAME}Targets)

include(JoinPaths)
join_paths(libdir_for_pc_file "\${exec_prefix}" "${CMAKE_INSTALL_LIBDIR}")
join_paths(includedir_for_pc_file "\${prefix}" "${CMAKE_INSTALL_INCLUDEDIR}")

# create config file
message("Creating project config file...")
configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/support/cmake/${PROJECT_NAME}Config.cmake.in
    ${PROJECT_CONFIG}
  INSTALL_DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
message("Created project config file at ${PROJECT_CONFIG}\n")

# generate the version file for the config file
write_basic_package_version_file(
	${VERSION_CONFIG}
	VERSION ${PACKAGE_VERSION}
	COMPATIBILITY AnyNewerVersion
)

message("Creating package config file...")
configure_file(
  ${PROJECT_SOURCE_DIR}/support/cmake/${PROJECT_NAME}.pc.in
  ${PACKAGE_CONFIG}
  @ONLY)
message("Created package config file at ${PACKAGE_CONFIG}\n")

message("Creating vcpkg manifest...")
configure_file(
  ${PROJECT_SOURCE_DIR}/support/vcpkg/vcpkg.json.in
  ${VCPKG_MNFST})
message("Created vcpkg manifest at ${VCPKG_MNFST}\n")

message("Creating vcpkg configuration...")
configure_file(
  ${PROJECT_SOURCE_DIR}/support/vcpkg/vcpkg-configuration.json.in
  ${VCPKG_CONFIG})
message("Created vcpkg configuration at ${VCPKG_CONFIG}\n")

message("Creating portfile...")
configure_file(
  ${PROJECT_SOURCE_DIR}/support/vcpkg/portfile.in.cmake
  ${PORT_FILE})
message("Created portfile at ${PORT_FILE}\n")

# create config header
message("Creating config header file...")
configure_file(
	${PROJECT_SOURCE_DIR}/support/cmake/${PROJECT_NAME}Config.h.in
	${CM_VARS_CONFIG})
message("Created config header file at ${CM_VARS_CONFIG}\n")

message("\n")

# ============================================================================ #
#
#                            Add target: "Foo.lib"
#
# ============================================================================ #

if(USE_FOO)
  message(STATUS "Foo enabled.")
  message(STATUS "Adding target...")

  # create library
  add_library(Foo STATIC)
  add_library(CMakeProject1::Foo ALIAS Foo)

  # Set target version.
  set_target_properties(Foo
    PROPERTIES
      VERSION ${LOCAL_VERSION_MAJOR}.${LOCAL_VERSION_MINOR}.${LOCAL_VERSION_PATCH}.${LOCAL_VERSION_TWEAK}
      SOVERSION ${LOCAL_VERSION_MAJOR}
      INTERFACE_Foo_MAJOR_VERSION ${LOCAL_VERSION_MAJOR})
  set_property(TARGET Foo APPEND PROPERTY COMPATIBLE_INTERFACE_STRING Foo_MAJOR_VERSION)

  # find and link to fmt package via vcpkg
  find_package(fmt CONFIG REQUIRED)
  target_link_libraries(Foo
    PUBLIC
      fmt::fmt
  )

  # Add source files and headers to target.
  target_sources(Foo
    PRIVATE
      ${PROJECT_SOURCE_DIR}/src/foo/foo.cpp
      ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/foo/foo.h
  )

  # add include directories
  target_include_directories(Foo
    PUBLIC
      $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/foo>
      $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/foo>
  )

  # install the c++ "foo" headers
  install(
    FILES ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/foo/foo.h
    DESTINATION ${${PROJECT_NAME}_INC_DIR}/foo
  )

  list(APPEND EXTRA_LIBS "Foo")
  list(APPEND INSTALL_TARGETS "Foo")

  message(STATUS "Added target: Foo.lib\n")

else(USE_FOO)
  message(STATUS "Foo disabled.\n")

endif(USE_FOO)

message("\n")

# ============================================================================ #
#
#                            Add target: "Tests.lib"
#
# ============================================================================ #

if(USE_TESTS)

  message(STATUS "Testing enabled.")
  message(STATUS "Adding target...")

  #enable CMake-style tests
  enable_testing()

  # test - does the application run?
  include(${CMAKE_CURRENT_LIST_DIR}/tests/run_from_bin_tree.cmake)

  # create library
  add_library(Tests STATIC)
  add_library(CMakeProject1::Tests ALIAS Tests)

  # Set target version.
  set_target_properties(Tests
    PROPERTIES
      VERSION ${LOCAL_VERSION_MAJOR}.${LOCAL_VERSION_MINOR}.${LOCAL_VERSION_PATCH}.${LOCAL_VERSION_TWEAK}
      SOVERSION ${LOCAL_VERSION_MAJOR}
      INTERFACE_Tests_MAJOR_VERSION ${LOCAL_VERSION_MAJOR})
  set_property(TARGET Tests APPEND PROPERTY COMPATIBLE_INTERFACE_STRING Tests_MAJOR_VERSION)

  find_package(Catch2 CONFIG REQUIRED)
  target_link_libraries(Tests
    PUBLIC
      Catch2::Catch2
  )

  # Add source files and headers to target.
  target_sources(Tests
    PRIVATE
      ${PROJECT_SOURCE_DIR}/src/test/test.cpp
      ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/test/test.h
  )

  # add include directories
  target_include_directories(Tests
    PUBLIC
      $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/test>
      $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/test>
  )

  # install the c++ "test" headers
  install(
    FILES ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/test/test.h
    DESTINATION ${${PROJECT_NAME}_INC_DIR}/test
  )

  list(APPEND EXTRA_LIBS "Tests")
  list(APPEND INSTALL_TARGETS "Tests")

  message(STATUS "Added target: Tests.lib\n")

else(USE_TESTS)

  message(STATUS "Testing disabled.\n")

endif(USE_TESTS)

message("\n")

# ============================================================================ #
#
#                            Add target: "Main.lib"
#
# ============================================================================ #

message(STATUS "Adding target...")

#add_library(Main STATIC ${CM_VARS_CONFIG})
#add_library(CMakeProject1::Main ALIAS Main)

add_executable(Main ${CM_VARS_CONFIG})

# Set target version.
set_target_properties(Main
  PROPERTIES
    VERSION ${LOCAL_VERSION_MAJOR}.${LOCAL_VERSION_MINOR}.${LOCAL_VERSION_PATCH}.${LOCAL_VERSION_TWEAK}
    SOVERSION ${LOCAL_VERSION_MAJOR}
    INTERFACE_Main_MAJOR_VERSION ${LOCAL_VERSION_MAJOR})
set_property(TARGET Main APPEND PROPERTY COMPATIBLE_INTERFACE_STRING Main_MAJOR_VERSION)

# Add source files and headers to target.
target_sources(Main
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src/main/main.cpp
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/main/main.h
)

# add include directories
target_include_directories(Main
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/main>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/main>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link any extra libraries to our "main" out...
target_link_libraries(Main
  PUBLIC
    ${EXTRA_LIBS}
)

# install the c++ "main" headers
install(
  FILES ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/main/main.h
  DESTINATION ${${PROJECT_NAME}_INC_DIR}/main
)

#list(APPEND EXTRA_LIBS Main)
list(APPEND INSTALL_TARGETS Main)

message(STATUS "Added target: Main.exe\n")

message("\n")

# ============================================================================ #
#
#                     Add target: "Executable.exe"
#
# ============================================================================ #

#add_executable(Executable ${CM_VARS_CONFIG})

#target_include_directories(Executable
#  PUBLIC
#    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
#    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
#)

#target_link_libraries(Executable PUBLIC Main)

#list(APPEND INSTALL_TARGETS Executable)

# Address sanitizer
if(ASAN_ENABLED)
  if(MSVC)
    target_compile_options(${INSTALL_TARGETS} PUBLIC /fsanitize=address)
  else()
    target_compile_options(${INSTALL_TARGETS} PUBLIC -fsanitize=address)
    target_link_options(${INSTALL_TARGETS} PUBLIC -fsanitize=address)
  endif()
endif()

# ============================================================================ #
#
#                               Install block
#
# ============================================================================ #

# install config header
install(
  FILES ${CM_VARS_CONFIG}
  DESTINATION ${${PROJECT_NAME}_INC_DIR}
)

# Install the library and headers.
install(
  TARGETS ${INSTALL_TARGETS}
  EXPORT ${TARGETS_EXPORT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
  FRAMEWORK DESTINATION "."
)

# Use a namespace because CMake provides better diagnostics for namespaced
# imported targets.
export(
  TARGETS ${INSTALL_TARGETS}
  NAMESPACE CMakeProject1::
  FILE ${PROJECT_BINARY_DIR}/${TARGETS_EXPORT_NAME}.cmake
)

# Install version, config and target files.
install(
  FILES
    ${PROJECT_CONFIG}
    ${VERSION_CONFIG}
  DESTINATION
    share/${PROJECT_NAME}
)

install(
  EXPORT ${TARGETS_EXPORT_NAME}
  DESTINATION share/${PROJECT_NAME}
  NAMESPACE CMakeProject1::
)

install(
  FILES ${PACKAGE_CONFIG}
  DESTINATION ${${PROJECT_NAME}_PKGCONFIG_DIR}
)

# install(
#  FILES
#    $<TARGET_PDB_FILE:${INSTALL_TARGETS}>
#  DESTINATION
#    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME} OPTIONAL
# )

message(STATUS "EXTRA_LIBS: \n" ${EXTRA_LIBS})
message("\n")

message(STATUS "CMAKE_MODULE_PATH: \n" ${CMAKE_MODULE_PATH})
message("\n")

message("\n")


message("CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})
message("CMAKE_CXX_FLAGS_DEBUG: " ${CMAKE_CXX_FLAGS_DEBUG})
message("CMAKE_CXX_FLAGS_RELEASE: " ${CMAKE_CXX_FLAGS_RELEASE})
message("CMAKE_CXX_FLAGS_MINSIZEREL: " ${CMAKE_CXX_FLAGS_MINSIZEREL})
message("CMAKE_CXX_FLAGS_RELWITHDEBINFO: " ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})

message("CMAKE_C_FLAGS = ${CMAKE_C_FLAGS}")
message("CMAKE_C_FLAGS_DEBUG = ${CMAKE_C_FLAGS_DEBUG}")
message("CMAKE_C_FLAGS_RELEASE = ${CMAKE_C_FLAGS_RELEASE}")
message("CMAKE_C_FLAGS_MINSIZEREL = ${CMAKE_C_FLAGS_MINSIZEREL}")
message("CMAKE_C_FLAGS_RELWITHDEBINFO = ${CMAKE_C_FLAGS_RELWITHDEBINFO}\n")
