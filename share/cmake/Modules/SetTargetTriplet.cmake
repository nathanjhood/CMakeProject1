macro(set_target_triplet)
    set(TARGET_TRIPLET_DEFAULT "${TARGET_TRIPLET_default}" CACHE STRING "Default target for which CMake will generate code." )
    if(TARGET_TRIPLET)
        message(WARNING "TARGET_TRIPLET is deprecated and will be removed in a future release. "
        "Please use TARGET_TRIPLET_DEFAULT instead.")
        set(TARGET_TRIPLET "${TARGET_TRIPLET}")
    else()
        set(TARGET_TRIPLET "${TARGET_TRIPLET_DEFAULT}")
    endif()
    message(STATUS "Detected target triplet: ${TARGET_TRIPLET}")
    message(STATUS "Detected default target triplet: ${TARGET_TRIPLET_DEFAULT}")
endmacro()
