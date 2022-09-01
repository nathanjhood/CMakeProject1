# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.

# CMake requirements.
cmake_minimum_required (VERSION 3.15)

# Toolchain location. Stores result in the CMakeCache.
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Toolchain file")

# Replace the "yourCompany" string with the name of the author/company of this project. Stores result in the CMakeCache.
set(COMPANY_NAME "yourCompany" CACHE STRING "Name of author/company")

# Create a CMake project here.
project (
	"CMakeProject1"
	VERSION 0.0.0.1
	DESCRIPTION "Generic CMake Project with in-built package manager"
	HOMEPAGE_URL https://stoneydsp.github.io/CMakeProject1/html/index.html
	LANGUAGES CXX
)

# Add source to this project's executable.
add_executable (CMakeProject1
	"${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/main.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/cfg/CMakeProject1_Config.h.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/cfg/CMakeProject1_Config.h"
)

# Check language requirements.
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeProject1 PROPERTY CXX_STANDARD 20)
endif()

# Add configuration file.
configure_file (
	"${CMAKE_CURRENT_SOURCE_DIR}/cfg/CMakeProject1_Config.h.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/cfg/CMakeProject1_Config.h"
)

# `target_sources` adds source files to a target. We pass the target that needs the sources as the
# first argument, then a visibility parameter for the sources which should normally be PRIVATE.
# Finally, we supply a list of source files that will be built into the target.
# This is a standard CMake command.
target_sources(CMakeProject1
    PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/main.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/cfg/CMakeProject1_Config.h.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/cfg/CMakeProject1_Config.h"
)

# If the target needs extra binary assets, they can be added here. The first argument is the name of
# a new static library target that will include all the binary resources. There is an optional
# `NAMESPACE` argument that can specify the namespace of the generated binary data class. Finally,
# the SOURCES argument should be followed by a list of source files that should be built into the
# static library. These source files can be of any kind (wav data, images, fonts, icons etc.).
# Conversion to binary-data will happen when the target is built.
# juce_add_binary_data(${CMAKE_PROJECT_NAME}_Data SOURCES ...)

# `target_link_libraries` links libraries and JUCE modules to other libraries or executables.
# Inter-module dependencies are resolved automatically. If you'd generated a binary data
# target above, you would need to link to it here too.

target_link_libraries (CMakeProject1
	PRIVATE
	# CMakeProject1_Data           # If we'd created a binary data target above, we'd link to it here
	fmt::fmt
	CppUnit
	juce::juce_core
	PUBLIC
	juce::juce_recommended_config_flags
	juce::juce_recommended_warning_flags
)

# Include sub-folder/projects.
add_subdirectory ("src")
add_subdirectory ("cfg")

# `target_compile_definitions` adds some preprocessor definitions to our target. In a Projucer
# project, these might be passed in the 'Preprocessor Definitions' field. JUCE modules also make use
# of compile definitions to switch certain features on/off, so if there's a particular feature you
# need that's not on by default, check the module header for the correct flag to set here. These
# definitions will be visible both to your code, and also the JUCE module code, so for new
# definitions, pick unique names that are unlikely to collide!
# This is a standard CMake command.
target_compile_definitions(CMakeProject1
    PRIVATE
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_console_app` call
        JUCE_USE_CURL=0    # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_console_app` call
)

# Host handling
if(WIN32)
    add_compile_definitions(WINDOWS=1)
endif ()

if (UNIX AND NOT APPLE)
    add_compile_definitions(LINUX=1)
endif ()

if (APPLE)
    add_compile_definitions(APPLE=1)
endif ()

if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_compile_definitions(_DEBUG=1)
else()
    add_compile_definitions(NDEBUG=1)
endif(${CMAKE_BUILD_TYPE} MATCHES Debug)

# Export options
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_ENABLE_EXPORTS on)

# Add tests and install targets if needed. Comment out if not required.
#include(CPACK)
#include(CTest)

# Enable testing. Comment out if not required.
#enable_testing()
