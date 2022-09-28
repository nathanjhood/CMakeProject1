# CMake requirements.
cmake_minimum_required(VERSION 3.7...3.24)
message("${CMAKE_CURRENT_SOURCE_DIR}/>")

find_program(DOXYGEN doxygen)
if (NOT DOXYGEN)
  message(STATUS "Target 'docs' disabled (requires doxygen)")
  return ()
endif ()

include(GNUInstallDirs)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html/
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/docs/${PROJECT_NAME} OPTIONAL
        PATTERN ".doctrees" EXCLUDE)
