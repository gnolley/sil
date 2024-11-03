
if(${ENABLE_WARNINGS})
    include(Warnings)
endif()

if(${ENABLE_LTO})
    include(LTO)
endif()

function(setup_target TARGET_NAME)

	if(${ENABLE_WARNINGS})
	    target_set_warnings(${TARGET_NAME} ${TARGET_NAME})
    endif()

    if(${ENABLE_LTO})
        target_enable_lto(${TARGET_NAME})
    endif()

    if(${CMAKE_BUILD_TYPE} STREQUAL "DEBUG")
        target_compile_definitions(${TARGET_NAME} PRIVATE ${SIL_DEBUG_FLAG})
    elseif(${CMAKE_BUILD_TYPE} STREQUAL "RELEASE")
        target_compile_definitions(${TARGET_NAME} PRIVATE ${SIL_RELEASE_FLAG})
    endif()

endfunction()