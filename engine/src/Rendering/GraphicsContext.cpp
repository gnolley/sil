#include "Rendering/GraphicsContext.h"

#include <GLFW/glfw3.h>
#include <algorithm>
#include <cassert>

Sil::GraphicsContext::GraphicsContext(const RenderConfig& config)
	: _config(config), _instance(GetCreateInfo(CreateAppInfo(_config), _validationLayers, _extensions)),
	_device(_instance, _config.RequiredFeatures)
{
}

VkApplicationInfo Sil::GraphicsContext::CreateAppInfo(const RenderConfig& config)
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

VkInstanceCreateInfo Sil::GraphicsContext::GetCreateInfo(const VkApplicationInfo& appInfo,
	std::vector<const char*>& layers,
	std::vector<const char*>& extensions)
{
	PopulateExtensionsList(extensions);
	PopulateValidationLayersList(layers);

	bool layersSupported = AreRequstedLayersSupported(layers);
	if (layersSupported == false)
	{
		throw std::runtime_error("Cannot enable validation layers! Layers not present.");
	};

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = static_cast<std::uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();
	createInfo.enabledLayerCount = layersSupported ? static_cast<std::uint32_t>(layers.size()) : 0;
	createInfo.ppEnabledLayerNames = layers.data();

	return createInfo;
}

bool Sil::GraphicsContext::AreRequstedLayersSupported(const std::vector<const char*>& layers) const
{
	if (layers.size() == 0)
	{
		return true;
	}

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

void Sil::GraphicsContext::PopulateExtensionsList(std::vector<const char*>& extensions) const
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	for (uint32_t i = 0; i < glfwExtensionCount; ++i)
	{
		extensions.push_back(glfwExtensions[i]);
	}

#if SIL_ENABLE_GFX_VALIDATION_LAYERS
	extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif
}

void Sil::GraphicsContext::PopulateValidationLayersList(std::vector<const char*>& layers) const
{
#if SIL_ENABLE_GFX_VALIDATION_LAYERS
	layers.push_back("VK_LAYER_KHRONOS_validation");
#endif // SIL_ENABLE_GFX_VALIDATION_LAYERS
}