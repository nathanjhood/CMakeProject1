# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.

# ------------------------- Configure CMake ---------------------------------- #

# CMake requirements.
cmake_minimum_required(VERSION 3.7...3.24)

# CMake policy.
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS YES)
set(ENABLE_LOGGING = 1)

message("Initiating CMake v${CMAKE_VERSION}")

# ------------------------- Configure External Modules ----------------------- #

# add required packages
message("Checking project dependencies...")
if(GIT_FOUND)
  message(STATUS "git: already found. Using: ${CMAKE_PROJECT_NAME} submodules")
else()
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.gitmodules)
    message(STATUS "git: adding local submodules...")
    add_subdirectory(extern)
  else()
    message(STATUS "git: no submodule file found")
  endif()
endif()

# ------------------------- Configure Project -------------------------------- #

message("${CMAKE_CURRENT_SOURCE_DIR}/>")

message("Detecting CMake project...")

# Create a CMake project here.
project (CMakeProject1
  VERSION
    1.0.0.0
  DESCRIPTION
    "VS Console Application with CMake, vcpkg, Doxygen, and JUCE support"
  HOMEPAGE_URL
    https://github.com/StoneyDSP/CMakeProject1
  LANGUAGES
    C CXX
)

message("...Detected project:\n")
message(STATUS "${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "${PROJECT_DESCRIPTION}")
message(STATUS "${PROJECT_HOMEPAGE_URL}\n")

# Configure folder structure.
set(RUNTIME_OUTPUT_DIRECTORY /artefacts)
set(ARCHIVE_OUTPUT_DIRECTORY /artefacts)
set(LIBRARY_OUTPUT_DIRECTORY /artefacts)
set(PDB_OUTPUT_DIRECTORY /bin)
set(PROJECT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

message(STATUS "set (RUNTIME_OUTPUT_DIRECTORY) <${RUNTIME_OUTPUT_DIRECTORY}>")
message(STATUS "set (ARCHIVE_OUTPUT_DIRECTORY) <${ARCHIVE_OUTPUT_DIRECTORY}>")
message(STATUS "set (LIBRARY_OUTPUT_DIRECTORY) <${LIBRARY_OUTPUT_DIRECTORY}>")
message(STATUS "set (PDB_OUTPUT_DIRECTORY) <${PDB_OUTPUT_DIRECTORY}>")
message(STATUS "set (PROJECT_BINARY_DIR) <${PROJECT_BINARY_DIR}>")
message(STATUS "set (PROJECT_SOURCE_DIR) <${PROJECT_SOURCE_DIR}>")

# Add output target.
message("Adding target...")
add_executable (${PROJECT_NAME} src/main.cpp src/main.h)
# Set target version
set_property(TARGET ${PROJECT_NAME} PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET ${PROJECT_NAME} PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET ${PROJECT_NAME} PROPERTY INTERFACE_${PROJECT_NAME}_MAJOR_VERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ${PROJECT_NAME}_MAJOR_VERSION)
message("Added target: ${PROJECT_NAME}.exe")


# include CMakePackageConfigHelpers macro.
include(CMakePackageConfigHelpers)
message(STATUS "Include (CMakePackageConfigHelpers)")

# specify the C++ standard.
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()


# include installer generator
include(CPack)
message(STATUS "Include (CPack)")

# make cache variables for install destinations
include(GNUInstallDirs)
message(STATUS "Include (GNUInstallDirs)")

# Packaging support
set(CPACK_PACKAGE_VENDOR "StoneyDSP")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "CMake Project with package management")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENCE)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
set(CPACK_SOURCE_GENERATOR TGZ;ZIP)
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

message(STATUS "CPack generators: ${CPACK_SOURCE_GENERATOR}")
message(STATUS "CPack ignores: ${CPACK_SOURCE_IGNORE_FILES}\n")

# ------------------------- Configure config files --------------------------- #

message(STATUS "Begin configure files...")

# generate the version file for the config file
message("Creating package version file...")
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)
if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake)
  message("Created package version file.")
else()
  message(FATAL_ERROR "Creating package version file failed!")
endif()

# create config file
message("Creating package config file...")
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  NO_CHECK_REQUIRED_COMPONENTS_MACRO)
message("Created package config file.")

# install config files
message("Installing package config file...")
install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
message("Installed package config file.")

# create config header for C++
message("Creating config header file...")
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.h)
message("Created config header file.")

message(STATUS "End configure files.\n")

# install header file
install(
  FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.h
  DESTINATION
    ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

# ------------------------- Packages and Sub-Projects ------------------------ #

#find_package(Catch2 CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)
message("found CMake package: Catch2 CONFIG REQUIRED")

#find_package(JUCE CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
message("found CMake package: fmt CONFIG REQUIRED")

find_package(StoneyDSP CONFIG REQUIRED)
message("found CMake package: StoneyDSP CONFIG REQUIRED")

# Include sub-folder/projects to the build tree.
message("Adding subdirectories...")
add_subdirectory (docs)
add_subdirectory (src)
add_subdirectory (cmake)
message("... Subdirectories added.")

message("${CMAKE_CURRENT_SOURCE_DIR}/>")

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    message(STATUS "Testing enabled. Adding to file tree.")
    add_subdirectory(tests)
else()
    message(STATUS "Testing disabled. Skipping tests directory.")
endif()

# link libraries and modules to other libraries or executables.
message(STATUS "Adding link libraries to project...")
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    fmt::fmt
    stoneydsp::stoneydsp_core
    Catch2::Catch2
    Catch2::Catch2WithMain
)
message(STATUS "...Link libraries added.")


# ------------------------- Begin Generic CMake Variable Logging ------------- #

# /*    C++ comment style not allowed   */

if(ENABLE_LOGGING EQUAL 1)

# if you are building in-source, this is the same as CMAKE_SOURCE_DIR, otherwise
# this is the top level directory of your build tree
MESSAGE( STATUS "CMAKE_BINARY_DIR:         " ${CMAKE_BINARY_DIR} )

# if you are building in-source, this is the same as CMAKE_CURRENT_SOURCE_DIR, otherwise this
# is the directory where the compiled or generated files from the current CMakeLists.txt will go to
MESSAGE( STATUS "CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR} )

# this is the directory, from which cmake was started, i.e. the top level source directory
MESSAGE( STATUS "CMAKE_SOURCE_DIR:         " ${CMAKE_SOURCE_DIR} )

# this is the directory where the currently processed CMakeLists.txt is located in
MESSAGE( STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR} )

# contains the full path to the top level directory of your build tree
MESSAGE( STATUS "PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR} )

# contains the full path to the root of your project source directory,
# i.e. to the nearest directory where CMakeLists.txt contains the PROJECT() command
MESSAGE( STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR} )

# set this variable to specify a common place where CMake should put all executable files
# (instead of CMAKE_CURRENT_BINARY_DIR)
MESSAGE( STATUS "EXECUTABLE_OUTPUT_PATH: " ${EXECUTABLE_OUTPUT_PATH} )

# set this variable to specify a common place where CMake should put all libraries
# (instead of CMAKE_CURRENT_BINARY_DIR)
MESSAGE( STATUS "LIBRARY_OUTPUT_PATH:     " ${LIBRARY_OUTPUT_PATH} )

# tell CMake to search first in directories listed in CMAKE_MODULE_PATH
# when you use FIND_PACKAGE() or INCLUDE()
MESSAGE( STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH} )

# this is the complete path of the cmake which runs currently (e.g. /usr/local/bin/cmake)
MESSAGE( STATUS "CMAKE_COMMAND: " ${CMAKE_COMMAND} )

# this is the CMake installation directory
MESSAGE( STATUS "CMAKE_ROOT: " ${CMAKE_ROOT} )

# this is the filename including the complete path of the file where this variable is used.
MESSAGE( STATUS "CMAKE_CURRENT_LIST_FILE: " ${CMAKE_CURRENT_LIST_FILE} )

# this is linenumber where the variable is used
MESSAGE( STATUS "CMAKE_CURRENT_LIST_LINE: " ${CMAKE_CURRENT_LIST_LINE} )

# this is used when searching for include files e.g. using the FIND_PATH() command.
MESSAGE( STATUS "CMAKE_INCLUDE_PATH: " ${CMAKE_INCLUDE_PATH} )

# this is used when searching for libraries e.g. using the FIND_LIBRARY() command.
MESSAGE( STATUS "CMAKE_LIBRARY_PATH: " ${CMAKE_LIBRARY_PATH} )

# the complete system name, e.g. "Linux-2.4.22", "FreeBSD-5.4-RELEASE" or "Windows 5.1"
MESSAGE( STATUS "CMAKE_SYSTEM: " ${CMAKE_SYSTEM} )

# the short system name, e.g. "Linux", "FreeBSD" or "Windows"
MESSAGE( STATUS "CMAKE_SYSTEM_NAME: " ${CMAKE_SYSTEM_NAME} )

# only the version part of CMAKE_SYSTEM
MESSAGE( STATUS "CMAKE_SYSTEM_VERSION: " ${CMAKE_SYSTEM_VERSION} )

# the processor name (e.g. "Intel(R) Pentium(R) M processor 2.00GHz")
MESSAGE( STATUS "CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR} )

# is TRUE on all UNIX-like OS's, including Apple OS X and CygWin
MESSAGE( STATUS "UNIX: " ${UNIX} )

# is TRUE on Windows, including CygWin
MESSAGE( STATUS "WIN32: " ${WIN32} )

# is TRUE on Apple OS X
MESSAGE( STATUS "APPLE: " ${APPLE} )

# is TRUE when using the MinGW compiler in Windows
MESSAGE( STATUS "MINGW: " ${MINGW} )

# is TRUE on Windows when using the CygWin version of cmake
MESSAGE( STATUS "CYGWIN: " ${CYGWIN} )

# is TRUE on Windows when using a Borland compiler
MESSAGE( STATUS "BORLAND: " ${BORLAND} )

# is TRUE on Windows when using a Borland compiler
MESSAGE( STATUS "_DEBUG: " ${_DEBUG} )

# is TRUE on Windows when using a Borland compiler
MESSAGE( STATUS "NDEBUG: " ${NDEBUG} )

# Microsoft compiler
MESSAGE( STATUS "MSVC: " ${MSVC} )
MESSAGE( STATUS "MSVC_IDE: " ${MSVC_IDE} )
MESSAGE( STATUS "MSVC60: " ${MSVC60} )
MESSAGE( STATUS "MSVC70: " ${MSVC70} )
MESSAGE( STATUS "MSVC71: " ${MSVC71} )
MESSAGE( STATUS "MSVC80: " ${MSVC80} )
MESSAGE( STATUS "CMAKE_COMPILER_2005: " ${CMAKE_COMPILER_2005} )


# set this to true if you don't want to rebuild the object files if the rules have changed,
# but not the actual source files or headers (e.g. if you changed the some compiler switches)
MESSAGE( STATUS "CMAKE_SKIP_RULE_DEPENDENCY: " ${CMAKE_SKIP_RULE_DEPENDENCY} )

# since CMake 2.1 the install rule depends on all, i.e. everything will be built before installing.
# If you don't like this, set this one to true.
MESSAGE( STATUS "CMAKE_SKIP_INSTALL_ALL_DEPENDENCY: " ${CMAKE_SKIP_INSTALL_ALL_DEPENDENCY} )

# If set, runtime paths are not added when using shared libraries. Default it is set to OFF
MESSAGE( STATUS "CMAKE_SKIP_RPATH: " ${CMAKE_SKIP_RPATH} )

# set this to true if you are using makefiles and want to see the full compile and link
# commands instead of only the shortened ones
MESSAGE( STATUS "CMAKE_VERBOSE_MAKEFILE: " ${CMAKE_VERBOSE_MAKEFILE} )

# this will cause CMake to not put in the rules that re-run CMake. This might be useful if
# you want to use the generated build files on another machine.
MESSAGE( STATUS "CMAKE_SUPPRESS_REGENERATION: " ${CMAKE_SUPPRESS_REGENERATION} )


# A simple way to get switches to the compiler is to use ADD_DEFINITIONS().
# But there are also two variables exactly for this purpose:

# the compiler flags for compiling C sources
MESSAGE( STATUS "CMAKE_C_FLAGS: " ${CMAKE_C_FLAGS} )

# the compiler flags for compiling C++ sources
MESSAGE( STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS} )


# Choose the type of build.  Example: SET(CMAKE_BUILD_TYPE Debug)
MESSAGE( STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE} )

# if this is set to ON, then all libraries are built as shared libraries by default.
MESSAGE( STATUS "BUILD_SHARED_LIBS: " ${BUILD_SHARED_LIBS} )

# the compiler used for C files
MESSAGE( STATUS "CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER} )

# the compiler used for C++ files
MESSAGE( STATUS "CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER} )

# if the compiler is a variant of gcc, this should be set to 1
MESSAGE( STATUS "CMAKE_COMPILER_IS_GNUCC: " ${CMAKE_COMPILER_IS_GNUCC} )

# if the compiler is a variant of g++, this should be set to 1
MESSAGE( STATUS "CMAKE_COMPILER_IS_GNUCXX : " ${CMAKE_COMPILER_IS_GNUCXX} )

# the tools for creating libraries
MESSAGE( STATUS "CMAKE_AR: " ${CMAKE_AR} )
MESSAGE( STATUS "CMAKE_RANLIB: " ${CMAKE_RANLIB} )

# Toolchain location.
MESSAGE( STATUS "CMAKE_TOOLCHAIN_FILE: " ${CMAKE_TOOLCHAIN_FILE} )

#
#MESSAGE( STATUS ": " ${} )

endif()

# ------------------------- End of Generic CMake Variable Logging ------------------
