#include "Rendering/Renderer.h"

#include "Vulkan/VkInstance.h"
#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>

#include <iostream>

Sil::Renderer::Renderer(const AppConfig appConfig, const EngineConfig engineConfig)
{
	std::cout << "Init Renderer" << "\n";

	// App Info
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = appConfig.ApplicationName.c_str();
	appInfo.applicationVersion = VK_MAKE_VERSION(
		appConfig.AppVersion.Major,
		appConfig.AppVersion.Minor,
		appConfig.AppVersion.Patch);
	appInfo.pEngineName = "Soliloquy";
	appInfo.engineVersion = VK_MAKE_VERSION(
		engineConfig.EngineVersion.Major,
		engineConfig.EngineVersion.Minor,
		engineConfig.EngineVersion.Patch);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;
	createInfo.enabledLayerCount = 0;

	_instance = std::make_unique<VkInstance>(&createInfo);
}