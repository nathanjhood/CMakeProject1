# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.

# CMake requirements.
cmake_minimum_required(VERSION 3.7...3.24)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# Toolchain location. Stores result in the CMakeCache.
set(CMAKE_TOOLCHAIN_FILE
  ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Toolchain file"
)

set_property(GLOBAL PROPERTY USE_FOLDERS YES)

# Create a CMake project here.
project (CMakeProject1
  VERSION
    1.0.0.0
  DESCRIPTION
    "Generic CMake Project with in-built package manager"
  HOMEPAGE_URL
    "https://stoneydsp.github.io/CMakeProject1/html/index.html"
  LANGUAGES
    C CXX
)

# make cache variables for install destinations
include(GNUInstallDirs)

# include CMakePackageConfigHelpers macro
include(CMakePackageConfigHelpers)

# set CMake module path
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# specify the C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

# specify the C++ standard
#if (CMAKE_VERSION VERSION_GREATER 3.12)
#  set_property(TARGET CMakeProject1 PROPERTY CXX_STANDARD 20)
#endif()

find_package (fmt CONFIG REQUIRED)
find_package(StoneyDSP CONFIG REQUIRED)

# generate the version file for the config file
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/CMakeProject1ConfigVersion.cmake
  VERSION ${version}
  COMPATIBILITY AnyNewerVersion
)

# create config file
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/CMakeProject1Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/CMakeProject1Config.cmake
  INSTALL_DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/CMakeProject1
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/CMakeProject1Config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/CMakeProject1Config.h
)

# install config files
install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/CMakeProject1Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/CMakeProject1ConfigVersion.cmake
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/CMakeProject1
)

# Include sub-folder/projects.
add_subdirectory (bin)
add_subdirectory (docs)
add_subdirectory (src)
add_subdirectory (tests)

# Add source to this project's executable.
add_executable (CMakeProject1 ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

# link libraries and modules to other libraries or executables.
target_link_libraries (CMakeProject1
	PRIVATE
    fmt::fmt
    stoneydsp::stoneydsp_core
	PUBLIC
)

# add source files to a target.
target_sources(CMakeProject1
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/CMakeProject1/main.h
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/CMakeProject1Config.h
)

# Add some preprocessor definitions to our target.
target_compile_definitions(CMakeProject1
    PRIVATE
)
