set(SIL_STAGEHAND_SOURCES "main.cpp")
add_executable(${COOK_TOOL_TARGET} ${SIL_STAGEHAND_SOURCES})

find_package(glslang CONFIG REQUIRED)
find_package(SPIRV-Tools CONFIG REQUIRED)
add_library(SPIRV-Tools ALIAS SPIRV-Tools-static)
find_package(SPIRV-Tools-opt CONFIG REQUIRED)
find_package(unofficial-shaderc_util CONFIG REQUIRED)
find_package(unofficial-shaderc CONFIG REQUIRED)

target_link_libraries(${COOK_TOOL_TARGET} PUBLIC unofficial::shaderc::shaderc)

if(${ENABLE_WARNINGS})
	target_set_warnings(${COOK_TOOL_TARGET} ${ENABLE_WARNINGS_AS_ERRORS})
endif()