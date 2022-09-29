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

# ============================================================================ #
#
#                             Configure CMake
#
# ============================================================================ #

# Top-level CMake project file, do global configuration
# and include sub-projects here.

# We can also define some useful options and set defaults here...
set(CMAKE_PROJECT_VENDOR "StoneyDSP")
option(ENABLE_LOGGING "Log cache variables to console terminal" OFF)
option(USE_EXTERN "Use extern folder to resolve dependencies" ON)
option(GIT_SUBMODULE "Check submodules during build" ON)
option(USE_VCPKG "Use local vcpkg if found" ON)
option(USE_FOO "Use foo" ON)
option(USE_TESTS "Use tests" ON)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
option(ASAN_ENABLED "Build this target with AddressSanitizer" OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Use external version file (could be optional?)
include(${CMAKE_CURRENT_LIST_DIR}/support/cmake/version-handling.cmake)

# get access to helper functions for creating config files
include(CMakePackageConfigHelpers)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
set(is_x64 TRUE)
else()
set(is_x64 FALSE)
endif()

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_CURRENT_SOURCE_DIR}/support/cmake
  ${CMAKE_CURRENT_SOURCE_DIR}/installed/share
)

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
message("CMAKE_INCLUDE_CURRENT_DIR = " ${CMAKE_INCLUDE_CURRENT_DIR})
message("\n")

# ============================================================================ #
#
#                           Configure Dependencies
#
# ============================================================================ #

# Get the list of ignored files from .gitignore.
set(GIT_IGNORE ${PROJECT_SOURCE_DIR}/.gitignore)

if(USE_EXTERN)
  # add required packages
  message(STATUS "Checking git...\n")
  message("\n")
  if(GIT_FOUND)
    message("git: already found. Using: ${CMAKE_PROJECT_NAME} submodules\n")
  else()
    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/.gitmodules)
      message("git: adding local submodules...\n")
      include(extern/CMakeLists.txt)
    else()
      message("git: no submodule file found\n")
    endif()
  endif()
  message(STATUS "${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt>\n")
endif()

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

message(STATUS "...Detected project:\n")
message("${PROJECT_NAME} v${PROJECT_VERSION}")
message("${PROJECT_DESCRIPTION}")
message("${PROJECT_HOMEPAGE_URL}")
message("@ ${PROJECT_VENDOR}\n")

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

message("CPACK_PACKAGE_VENDOR = ${CPACK_PACKAGE_VENDOR}")
message("CPACK_PACKAGE_DESCRIPTION_SUMMARY = ${PROJECT_DESCRIPTION}")
message("CPACK_PACKAGE_VERSION_MAJOR = ${LOCAL_VERSION_MAJOR}")
message("CPACK_PACKAGE_VERSION_MINOR = ${LOCAL_VERSION_MINOR}")
message("CPACK_PACKAGE_VERSION_PATCH = ${LOCAL_VERSION_PATCH}")
message("CPACK_RESOURCE_FILE_LICENSE = ${CMAKE_CURRENT_LIST_DIR}/LICENCE")
message("CPACK_RESOURCE_FILE_README = ${CMAKE_CURRENT_LIST_DIR}/README.md")
message("CPACK_SOURCE_GENERATOR = ${CPACK_SOURCE_GENERATOR}")
message("CPack ignores: ${CPACK_SOURCE_IGNORE_FILES}\n")

# include installer generator
include(CPack)

# ============================================================================ #
#
#                           Configure Folders
#
# ============================================================================ #

# make cache variables for install destinations
include(GNUInstallDirs)

# Configure folder structure.
set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(PDB_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# ============================================================================ #
#
#                           Configure Project
#
# ============================================================================ #

set(${PROJECT_NAME}_CMAKE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME} CACHE STRING "Installation directory for cmake files, a relative path that will be joined with ${CMAKE_INSTALL_PREFIX} or an absolute path.")
set(${PROJECT_NAME}_INC_DIR ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME} CACHE STRING "Installation directory for include files, a relative path that will be joined with ${CMAKE_INSTALL_PREFIX} or an absolute path.")
set(VERSION_CONFIG ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake)
set(PROJECT_CONFIG ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake)
set(CM_VARS_CONFIG ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h)
set(PKGCONFIG ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc)
set(TARGETS_EXPORT_NAME ${PROJECT_NAME}Targets)
set(${PROJECT_NAME}_LIB_DIR ${CMAKE_INSTALL_LIBDIR} CACHE STRING "Installation directory for libraries, a relative path that will be joined to ${CMAKE_INSTALL_PREFIX} or an absolute path.")
set(${PROJECT_NAME}_PKGCONFIG_DIR ${CMAKE_INSTALL_LIBDIR}/pkgconfig CACHE PATH "Installation directory for pkgconfig (.pc) files, a relative path that will be joined with ${CMAKE_INSTALL_PREFIX} or an absolute path.")

# create config file
configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/support/cmake/${PROJECT_NAME}Config.cmake.in
    ${PROJECT_CONFIG}
  INSTALL_DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# generate the version file for the config file
write_basic_package_version_file(
	${VERSION_CONFIG}
	VERSION ${PACKAGE_VERSION}
	COMPATIBILITY AnyNewerVersion
)

configure_file(
  ${PROJECT_SOURCE_DIR}/support/cmake/${PROJECT_NAME}.pc.in
  ${PKGCONFIG}
  @ONLY)

# create config header
configure_file(
	${PROJECT_SOURCE_DIR}/support/cmake/${PROJECT_NAME}Config.h.in
	${CM_VARS_CONFIG})

# install config header
install(
  FILES ${CM_VARS_CONFIG}
  DESTINATION ${${PROJECT_NAME}_INC_DIR}
)

# ============================================================================ #
#
#                            Add target: "Foo.lib"
#
# ============================================================================ #

if(USE_FOO)

message(STATUS "Adding target...\n")

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

# Address sanitizer
if(ASAN_ENABLED)
  if(MSVC)
    target_compile_options(Foo PUBLIC /fsanitize=address)
  else()
    target_compile_options(Foo PUBLIC -fsanitize=address)
    target_link_options(Foo PUBLIC -fsanitize=address)
  endif()
endif()

# install the c++ "foo" headers
install(
  FILES ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/foo/foo.h
  DESTINATION ${${PROJECT_NAME}_INC_DIR}/foo
)

list(APPEND EXTRA_LIBS Foo)
list(APPEND INSTALL_TARGETS Foo)

message("Added target: Foo.lib\n")

endif(USE_FOO)

# ============================================================================ #
#
#                            Add target: "Tests.lib"
#
# ============================================================================ #

if(USE_TESTS)

message(STATUS "Testing enabled.\n")
message(STATUS "Adding target...\n")

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

# Address sanitizer
if(ASAN_ENABLED)
  if(MSVC)
    target_compile_options(Tests PUBLIC /fsanitize=address)
  else()
    target_compile_options(Tests PUBLIC -fsanitize=address)
    target_link_options(Tests PUBLIC -fsanitize=address)
  endif()
endif()

# install the c++ "test" headers
install(
  FILES ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/test/test.h
  DESTINATION ${${PROJECT_NAME}_INC_DIR}/test
)

list(APPEND EXTRA_LIBS Tests)
list(APPEND INSTALL_TARGETS Tests)

message("Added target: Tests.lib\n")

else(USE_TESTS)
message(STATUS "Testing disabled.\n")

endif(USE_TESTS)

# ============================================================================ #
#
#                            Add target: "Main.lib"
#
# ============================================================================ #

message(STATUS "Adding target...\n")

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
)

# Link any extra libraries to our "main" out...
target_link_libraries(Main
  PUBLIC
    ${EXTRA_LIBS}
)

# Address sanitizer
if(ASAN_ENABLED)
  if(MSVC)
    target_compile_options(Main PUBLIC /fsanitize=address)
  else()
    target_compile_options(Main PUBLIC -fsanitize=address)
    target_link_options(Main PUBLIC -fsanitize=address)
  endif()
endif()

# install the c++ "main" headers
install(
  FILES ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/main/main.h
  DESTINATION ${${PROJECT_NAME}_INC_DIR}/main
)

#list(APPEND EXTRA_LIBS Main)
list(APPEND INSTALL_TARGETS Main)

message("Added target: Main.exe\n")

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

# ============================================================================ #
#
#                               Install block
#
# ============================================================================ #

# Install the library and headers.
install(
  TARGETS ${INSTALL_TARGETS}
  EXPORT ${TARGETS_EXPORT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
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
  FILES ${PKGCONFIG}
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

#install(
#  FILES
#    $<TARGET_PDB_FILE:${INSTALL_TARGETS}>
#  DESTINATION
#    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME} OPTIONAL
#)
