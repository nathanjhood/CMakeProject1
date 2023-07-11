macro(get_source_info)
    find_package(Git QUIET)
    if(GIT_FOUND)
        execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse --git-dir
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            RESULT_VARIABLE test_result
            OUTPUT_VARIABLE git_output
        )
        if(test_result EQUAL 0)
            # If we found a '/.git' at the project root, fetch the full path and
            # store it as 'git_dir'
            get_filename_component(git_dir ${git_output} ABSOLUTE BASE_DIR "${CMAKE_SOURCE_DIR}")
            string(STRIP "${git_dir}" git_dir)
            execute_process(
                COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                RESULT_VARIABLE test_result
                OUTPUT_VARIABLE git_revision
            )
            if(test_result EQUAL 0)
                # If our VCS found a revision number, pass it to cache
                string(STRIP "${git_revision}" git_revision)
                # message(STATUS "git_revision = ${git_revision}")
            endif()

            execute_process(
                COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref --symbolic-full-name HEAD
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                RESULT_VARIABLE test_result
                OUTPUT_VARIABLE git_remote
            )
            if(test_result EQUAL 0)
                string(REPLACE "/" ";" branch ${git_remote})
                list(GET branch 0 git_remote)

            else()
                set(git_remote "origin")
            endif()
            # message(STATUS "git_remote = ${git_remote}")

            execute_process(
                COMMAND ${GIT_EXECUTABLE} remote get-url origin #${remote}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                RESULT_VARIABLE test_result
                OUTPUT_VARIABLE git_url
            )
            if(test_result EQUAL 0)
                string(STRIP "${git_url}" git_url)
                string(REPLACE "\n" "" git_url ${git_url})
            else()
            endif()
        endif()

        # message(STATUS "git_url = ${git_url}")
        # message(STATUS "git_dir = ${git_dir}")
    else()
        message(WARNING "Git not found. Version cannot be determined.")
    endif()
endmacro()

# set(HEADER_FILE "version.h")
# file(WRITE "${HEADER_FILE}.tmp" "// Version control info \n")
# file(APPEND "${HEADER_FILE}.tmp" "#define ${PROJECT_NAME}_VERSION_MAJOR \"${PROJECT_VERSION_MAJOR}\"\n")
# file(APPEND "${HEADER_FILE}.tmp" "#define ${PROJECT_NAME}_VERSION_MINOR \"${PROJECT_VERSION_MINOR}\"\n")
# file(APPEND "${HEADER_FILE}.tmp" "#define ${PROJECT_NAME}_VERSION_PATCH \"${PROJECT_VERSION_PATCH}\"\n")
# if(git_revision)
#     file(APPEND "${HEADER_FILE}.tmp" "#define ${PROJECT_NAME}_VERSION_TWEAK \"${git_revision}\"\n")
# else()
#     file(APPEND "${HEADER_FILE}.tmp" "#undef ${PROJECT_NAME}_VERSION_TWEAK\n")
# endif()
# if(git_url)
#     file(APPEND "${HEADER_FILE}.tmp" "#define ${PROJECT_NAME}_REPOSITORY \"${git_url}\"\n")
# else()
#     file(APPEND "${HEADER_FILE}.tmp" "#undef ${PROJECT_NAME}_REPOSITORY\n")
# endif()
# #Copy the file only if it has changed.
# execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different "${HEADER_FILE}.tmp" "${HEADER_FILE}")
# # file(REMOVE "${HEADER_FILE}.tmp")
