#pragma once

#include <vulkan/vulkan_core.h>
#include "Vulkan/VkInstance.h"

namespace Sil
{
	static class VkDeviceSelector
	{
	public:
		static const VkPhysicalDevice SelectDevice(const VkInstance& instance);

	private:
		static const std::uint32_t CalculateDeviceHeuristic(VkPhysicalDevice& device);
	};
}