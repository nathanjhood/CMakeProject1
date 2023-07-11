#[===[
Returns the host triplet.

Invokes "config.guess" if necessary.

]===]
macro(get_host_triplet var)
    if(MSVC)
        if(CMAKE_C_COMPILER_ARCHITECTURE_ID MATCHES "ARM64.*")
            set(value "aarch64-pc-windows-msvc")
        elseif(CMAKE_C_COMPILER_ARCHITECTURE_ID MATCHES "ARM.*")
            set(value "armv7-pc-windows-msvc")
        elseif(CMAKE_C_COMPILER_ARCHITECTURE_ID STREQUAL "x64")
            set(value "x86_64-pc-windows-msvc")
        elseif(CMAKE_C_COMPILER_ARCHITECTURE_ID STREQUAL "X86")
            set(value "i686-pc-windows-msvc")
        elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(value "x86_64-pc-windows-msvc")
        else()
            set(value "i686-pc-windows-msvc")
        endif()
    elseif(MINGW)
        # CMake doesn't provide COMPILER_ARCHITECTURE_ID for Clang/GCC,
        # but it does for MSVC.
        if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "ARM.*")
            if(CMAKE_SIZEOF_VOID_P EQUAL 8)
                set(value "aarch64-w64-windows-gnu")
            else()
                set(value "armv7-w64-windows-gnu")
            endif()
        else()
            if(CMAKE_SIZEOF_VOID_P EQUAL 8)
                set(value "x86_64-w64-windows-gnu")
            else()
                set(value "i686-w64-windows-gnu")
            endif()
        endif()
    elseif(CMAKE_SYSTEM_NAME MATCHES "OS390")
        set(value "s390x-ibm-zos")
    elseif(CMAKE_SYSTEM_NAME STREQUAL AIX)
        # We defer to dynamic detection of the host AIX version.
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(value "powerpc64-ibm-aix")
        else()
            set(value "powerpc-ibm-aix")
        endif()
    else(MSVC)
        if(CMAKE_HOST_SYSTEM_NAME STREQUAL Windows AND NOT MSYS)
            message(WARNING "unable to determine host target triplet")
        else()
            set(config_guess ${CMAKE_CURRENT_LIST_DIR}/config.guess)
            execute_process(
                COMMAND sh ${config_guess}
                RESULT_VARIABLE TT_RV
                OUTPUT_VARIABLE TT_OUT
                OUTPUT_STRIP_TRAILING_WHITESPACE
            )
            if(NOT TT_RV EQUAL 0)
                message(FATAL_ERROR "Failed to execute ${config_guess}")
            endif(NOT TT_RV EQUAL 0)
            set(value ${TT_OUT})
        endif()
    endif(MSVC)
    set(${var} ${value} PARENT_SCOPE)
    message(STATUS "Detected host triplet: ${value}")
    unset(var)
    unset(value)
endmacro(get_host_triplet var)
