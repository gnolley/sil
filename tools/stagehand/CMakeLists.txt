set(SIL_STAGEHAND_SOURCES "main.cpp"
	"AssetProcessors.hpp" "Processors/ShaderProcessor.hpp"
	"StreamBuilders.hpp"
)

add_executable(${COOK_TOOL_TARGET} ${SIL_STAGEHAND_SOURCES})
target_include_directories(${COOK_TOOL_TARGET} PUBLIC "${COOK_TOOL_DIR}/includes/")

add_custom_target(${BUILD_BUILTIN_ASSETS_TARGET}
	COMMAND ${COOK_TOOL_TARGET} -i "${CMAKE_SOURCE_DIR}/builtin_resources" -o "${CMAKE_BINARY_DIR}/builtin_resources"
	COMMENT "Building builtin assets from ${CMAKE_SOURCE_DIR}/builtin_resources to ${CMAKE_BINARY_DIR}/builtin"
	DEPENDS ${COOK_TOOL_TARGET}
)

add_dependencies(${BUILD_BUILTIN_ASSETS_TARGET} ${COOK_TOOL_TARGET})

# Shader tools
find_package(glslang CONFIG REQUIRED)
find_package(SPIRV-Tools CONFIG REQUIRED)
add_library(SPIRV-Tools ALIAS SPIRV-Tools-static)
find_package(SPIRV-Tools-opt CONFIG REQUIRED)
find_package(unofficial-shaderc_util CONFIG REQUIRED)
find_package(unofficial-shaderc CONFIG REQUIRED)

# Command line arguments
find_package(CLI11 CONFIG REQUIRED)

target_link_libraries(${COOK_TOOL_TARGET} PRIVATE unofficial::shaderc::shaderc CLI11::CLI11)

if(${ENABLE_WARNINGS})
	target_set_warnings(${COOK_TOOL_TARGET} ${ENABLE_WARNINGS_AS_ERRORS})
endif()

