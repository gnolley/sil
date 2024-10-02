#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>
#include <algorithm>

#include "Config/RenderConfig.h"
#include "Debug/Logger.h"

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

bool AreRequstedLayersSupported(const std::vector<const char*>& layers)
{
	std::uint32_t numInstanceLayerProperties{};
	vkEnumerateInstanceLayerProperties(&numInstanceLayerProperties, nullptr);

	auto props = std::vector<VkLayerProperties>(numInstanceLayerProperties);
	vkEnumerateInstanceLayerProperties(&numInstanceLayerProperties, props.data());

	return std::all_of(layers.begin(), layers.end(),
		[&props](const char* layer) {
			auto matchFn = [layer](const VkLayerProperties& prop) { return std::strcmp(prop.layerName, layer) == 0; };
			auto result = std::ranges::find_if(props.begin(), props.end(), matchFn);
			return result != std::ranges::end(props);
		});
}

VkInstanceCreateInfo GetCreateInfo(VkApplicationInfo& appInfo, const std::vector<const char*>& validationLayers)
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	bool layersSupported = AreRequstedLayersSupported(validationLayers);
	if (layersSupported == false)
	{
		throw std::runtime_error("Cannot enable validation layers! Layers not present.");
	};

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;
	createInfo.enabledLayerCount = layersSupported ? static_cast<std::uint32_t>(validationLayers.size()) : 0;
	createInfo.ppEnabledLayerNames = validationLayers.data();

	return createInfo;
}