set(SIL_COR_SOURCES
	"SilEngine.cpp"
)

add_library(${ENGINE_SRC_TARGET} STATIC ${SIL_COR_SOURCES})

if(${ENABLE_WARNINGS})
	target_set_warnings(${ENGINE_SRC_TARGET} ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(${ENGINE_SRC_TARGET})
endif()