#pragma once

#include <vector>
#include <vulkan/vulkan_core.h>

#include "Config/RenderConfig.h"
#include "Vulkan/VkInstance.h"

namespace Sil
{

	class GraphicsContext
	{
	public:
		explicit GraphicsContext(const RenderConfig& config);

		inline const RenderConfig& GetRenderConfig() const { return _config; };
		inline const VkInstance& GetVkInstance() const { return _instance; }

		inline const size_t NumEnabledExtensions() const { return _extensions.size(); }
		inline const size_t NumEnabledValidationLayers() const { return _validationLayers.size(); }

	private:
		// should be initialised first.
		std::vector<const char*> _extensions;
		std::vector<const char*> _validationLayers;

		const RenderConfig _config;
		const VkInstance _instance;

		bool AreRequstedLayersSupported(const std::vector<const char*>& layers) const;
		void PopulateValidationLayersList(std::vector<const char*>& layers) const;
		void PopulateExtensionsList(std::vector<const char*>& extensions) const;

		VkApplicationInfo CreateAppInfo(const RenderConfig& config);
		VkInstanceCreateInfo GetCreateInfo(const VkApplicationInfo& appInfo, 
			std::vector<const char*>& layers, 
			std::vector<const char*>& extensions);
	};

}