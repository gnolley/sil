#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>

#include "Config/RenderConfig.h"

VkApplicationInfo CreateAppInfo(Sil::RenderConfig& config)
{
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = config.AppName.data();
	appInfo.applicationVersion = VK_MAKE_API_VERSION(
		0U,
		config.AppVersion.Major,
		config.AppVersion.Minor,
		config.AppVersion.Patch);
	appInfo.pEngineName = "Soliloquy"; // TODO: Find a nicer way to get this.
	appInfo.engineVersion = VK_MAKE_API_VERSION(
		0U,
		config.EngineVersion.Major,
		config.EngineVersion.Minor,
		config.EngineVersion.Patch);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	return appInfo;
}

VkInstanceCreateInfo GetCreateInfo(VkApplicationInfo& appInfo)
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;
	createInfo.enabledLayerCount = 0;

	return createInfo;
}