function(target_set_warnings TARGET AS_ERRORS)

    set(MSVC_WARNINGS
        /W4
        /permissive-)
    
    set(CLANG_WARNINGS
        -Wall
        -Wextra
        -Wpedantic)

    set(GCC_WARNINGS ${CLANG_WARNINGS})

    if(${AS_ERRORS})
        set(MSVC_WARNINGS ${MSVC_WARNINGS} /WX)
        set(CLANG_WARNINGS ${CLANG_WARNINGS} /-Werror)
        set(GCC_WARNINGS ${GCC_WARNINGS} -Werror)
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        set(WARNINGS ${MSVC_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "CLANG")
        set(WARNINGS ${CLANG_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(WARNINGS ${GCC_WARNINGS})
    endif()

    target_compile_options(${TARGET} PRIVATE ${WARNINGS})
    message("Warnings: " /${WARNINGS})

endfunction()