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

option(USE_EXTERN "Use extern folder to resolve dependencies" ON)

if(USE_EXTERN)
  # add required packages
  message("Checking project dependencies...")
  if(GIT_FOUND)
    message(STATUS "git: already found. Using: ${CMAKE_PROJECT_NAME} submodules")
  else()
    if(EXISTS ${CMAKE_SOURCE_DIR}/.gitmodules)
      message(STATUS "git: adding local submodules...")
      include(extern/CMakeLists.txt)
    else()
      message(STATUS "git: no submodule file found")
    endif()
  endif()
endif()

# ---------------------------------------------------------------------------- #
#
#                             Configure Project
#
# ---------------------------------------------------------------------------- #
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

message(STATUS "...Detected project:\n")
message("${PROJECT_NAME} v${PROJECT_VERSION}")
message("${PROJECT_DESCRIPTION}")
message("${PROJECT_HOMEPAGE_URL}\n")

# Check if we are in the top-level project or not:
if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "${PROJECT_NAME} is a sub-project of ${CMAKE_PROJECT_NAME}")
else()
    message(STATUS "${CMAKE_PROJECT_NAME} is a top-level project")
endif()

# Configure folder structure.
set(PROJECT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(PDB_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_INTDIR ${PROJECT_BINARY_DIR}/artefacts)

message("set (PROJECT_BINARY_DIR) <${PROJECT_BINARY_DIR}>")
message("set (PROJECT_SOURCE_DIR) <${PROJECT_SOURCE_DIR}>")
message("set (RUNTIME_OUTPUT_DIRECTORY) <${RUNTIME_OUTPUT_DIRECTORY}>")
message("set (ARCHIVE_OUTPUT_DIRECTORY) <${ARCHIVE_OUTPUT_DIRECTORY}>")
message("set (LIBRARY_OUTPUT_DIRECTORY) <${LIBRARY_OUTPUT_DIRECTORY}>")
message("set (PDB_OUTPUT_DIRECTORY) <${PDB_OUTPUT_DIRECTORY}>")
message("set (CMAKE_INTDIR) <${CMAKE_INTDIR}>\n")
