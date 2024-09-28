function(target_enable_lto TARGET)

    include(CheckIPOSupported)
    check_ipo_supported(RESULT result)

    if(result)
        message(STATUS "IPO/LTO supported")
        set_property(TARGET ${TARGET} PROPERTY INTERPROCEDURAL_OPTIMIZATION True)
    else()
        message(ERROR "IPO/LTO Not supported!")
    endif()

endfunction()