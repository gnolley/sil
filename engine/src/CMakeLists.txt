set(SIL_COR_INCLUDES 
	"${ENGINE_DIR}/includes/"
	${Vulkan_INCLUDE_DIRS}
)

set(SIL_COR_SOURCES
 "SilEngine.cpp"
 "Rendering/Window.cpp" "Rendering/Renderer.cpp" 
 "Subsystems/RenderingSubsystem.cpp" "Debug/Logger.cpp"  
 "Rendering/GraphicsContext.cpp" "Debug/VulkanDebugAdaptor.cpp"
 "Rendering/GraphicsDevice.cpp" "Vulkan/VkDeviceSelector.cpp"
 "Vulkan/VkSurface.cpp" "Config/RenderingFeatures.cpp" "Rendering/Swapchain.cpp")

add_library(${ENGINE_SRC_TARGET} STATIC ${SIL_COR_SOURCES})
target_include_directories(${ENGINE_SRC_TARGET} PUBLIC ${SIL_COR_INCLUDES})

target_link_libraries(${ENGINE_SRC_TARGET} PUBLIC glfw Vulkan::Vulkan)
target_link_libraries(${ENGINE_SRC_TARGET} PRIVATE ${PLAYBOOK_LIB_TARGET})
add_dependencies(${ENGINE_SRC_TARGET} ${BUILD_BUILTIN_ASSETS_TARGET})

setup_target(${ENGINE_SRC_TARGET})

if(${ENABLE_VK_VALIDATION_LAYERS})
    target_compile_definitions(${ENGINE_SRC_TARGET} PRIVATE ${SIL_VK_LAYERS_FLAG})
endif()