#pragma once

#include <vulkan/vulkan_core.h>
#include "Config/RenderConfig.h"

#include "Vulkan/VkSurface.h"
#include "Vulkan/VkInstance.h"

namespace Sil
{
	class VkDeviceSelector
	{
	public:
		static const VkPhysicalDevice SelectDevice(const VkInstance& instance, const VkSurface& surface, 
			const RequiredRenderFeatures& features);

	private:
		static const std::uint32_t CalculateDeviceHeuristic(VkPhysicalDevice& device);
		static const bool IsDeviceSupported(const VkPhysicalDevice& device, 
			const VkSurface& surface, const RequiredRenderFeatures& features);
	};
}