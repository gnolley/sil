set(SIL_COR_SOURCES
 "SilEngine.cpp"
 "Rendering/Window.cpp" "Rendering/Renderer.cpp" 
 "Subsystems/RenderingSubsystem.cpp" "Debug/Logger.cpp")

add_library(${ENGINE_SRC_TARGET} STATIC ${SIL_COR_SOURCES})

target_link_libraries(${ENGINE_SRC_TARGET} PUBLIC glfw Vulkan::Vulkan)

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

if(${ENABLE_VK_VALIDATION_LAYERS})
    target_compile_definitions(${ENGINE_SRC_TARGET} PRIVATE ${SIL_VK_LAYERS_FLAG})
endif()