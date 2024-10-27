set(SIL_STAGEHAND_SOURCES "main.cpp"
	"AssetProcessors.hpp" "Processors/ShaderProcessor.hpp"
	"StreamBuilders.hpp"
)

add_executable(${COOK_TOOL_TARGET} ${SIL_STAGEHAND_SOURCES})
target_include_directories(${COOK_TOOL_TARGET} PUBLIC "${COOK_TOOL_DIR}/includes/")

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