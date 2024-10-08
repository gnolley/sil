#pragma once

#include <Config/RenderConfig.h>
#include <vulkan/vulkan_core.h>
#include "Vulkan/VkInstance.h"

namespace Sil
{
	class VkDeviceSelector
	{
	public:
		static const VkPhysicalDevice SelectDevice(const VkInstance& instance, const RequiredRenderFeatures& features);

	private:
		static const std::uint32_t CalculateDeviceHeuristic(VkPhysicalDevice& device);
		static const bool IsDeviceSupported(VkPhysicalDevice& device, const RequiredRenderFeatures& features);
	};
}