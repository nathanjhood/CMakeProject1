# CMake requirements.
cmake_minimum_required(VERSION 3.7...3.24)
message("${CMAKE_CURRENT_SOURCE_DIR}/>")

# does the application run
add_test(NAME Runs COMMAND CMakeProject1 25)

# define a function to simplify adding tests
function(do_test target arg result)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  set_tests_properties(Comp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()
