
if(${ENABLE_WARNINGS})
    include(Warnings)
endif()

if(${ENABLE_LTO})
    include(LTO)
endif()

function(setup_target TARGET_NAME)

	if(${ENABLE_WARNINGS})
	    target_set_warnings(${ENGINE_SRC_TARGET} ${ENABLE_WARNINGS_AS_ERRORS})
    endif()

    if(${ENABLE_LTO})
        target_enable_lto(${ENGINE_SRC_TARGET})
    endif()

    if(${CMAKE_BUILD_TYPE} STREQUAL "DEBUG")
        target_compile_definitions(${ENGINE_SRC_TARGET} PRIVATE ${SIL_DEBUG_FLAG})
    elseif(${CMAKE_BUILD_TYPE} STREQUAL "RELEASE")
        target_compile_definitions(${ENGINE_SRC_TARGET} PRIVATE ${SIL_RELEASE_FLAG})
    endif()

endfunction()