#pragma once
#include <cstdint>
#include <vector>

#include <vulkan/vulkan_core.h>
#include "Vulkan/VkDevice.h"
#include "Config/RenderConfig.h"

namespace Sil {
	enum QueueType {
		Graphics,
		Transfer,
		Compute,
	};

	class GraphicsDevice
	{
	public:
		GraphicsDevice(VkPhysicalDevice& device, RequiredRenderFeatures requiredFeatures);

		const VkDevice& GetDevice() const;

	private:

		void GetCreateInfo(const VkPhysicalDevice& device);

		const std::vector<VkDeviceQueueCreateInfo> GetRequiredQueues(const VkPhysicalDevice& device, 
			const std::vector<QueueType>& requiredQueues) const;
	};
}