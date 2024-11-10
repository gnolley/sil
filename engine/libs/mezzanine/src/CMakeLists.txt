set(MEZZANINE_LIB_SRC 
 "Mezzanine.cpp" "Rendering/Window.cpp" "Rendering/Renderer.cpp"
 "Rendering/GraphicsContext.cpp" "Debug/VulkanDebugAdaptor.cpp"
 "Rendering/GraphicsDevice.cpp" "Vulkan/VkDeviceSelector.cpp"
 "Vulkan/VkSurface.cpp" "Rendering/Swapchain.cpp"
)

add_library(${MEZZANINE_LIB_TARGET} STATIC ${MEZZANINE_LIB_SRC})

target_include_directories(${MEZZANINE_LIB_TARGET} PUBLIC ${MEZZANINE_INCLUDE_DIR} ${Vulkan_INCLUDE_DIRS} ${PLAYBOOK_INCLUDE_DIR} ${CORE_INCLUDE_DIR})

target_link_libraries(${MEZZANINE_LIB_TARGET} PUBLIC glfw Vulkan::Vulkan ${PLAYBOOK_LIB_TARGET} ${CORE_LIB_TARGET})

setup_target(${MEZZANINE_LIB_TARGET})

if(${ENABLE_VK_VALIDATION_LAYERS})
    target_compile_definitions(${MEZZANINE_LIB_TARGET} PRIVATE ${SIL_VK_LAYERS_FLAG})
endif()