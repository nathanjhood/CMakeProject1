# CMake requirements.
cmake_minimum_required(VERSION 3.7...3.24.2)

# ============================================================================ #
#
#                 				Add tests to project
#
# ============================================================================ #

#enable CMake-style tests
enable_testing()

# does the application run
include(${CMAKE_CURRENT_LIST_DIR}/run_from_bin_tree.cmake)

# create library
add_library(tests STATIC)
add_library(CMakeProject1::tests ALIAS tests)

find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(tests
  PRIVATE
	  Catch2::Catch2
)

# Add source files and headers to target.
target_sources(tests
  PRIVATE
    ${PROJECT_SOURCE_DIR}/tests/test.cpp
    ${PROJECT_SOURCE_DIR}/tests/test.h
)

# add include directories
target_include_directories(tests
	PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# install the target and create export-set
#install(TARGETS tests
#        EXPORT tests_Targets
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/tests
#)

# generate and install export file
#install(EXPORT tests_Targets
#        FILE tests_Targets.cmake
#        NAMESPACE CMakeProject1::tests
#        DESTINATION share/${PROJECT_NAME}
#)
