#pragma once
#include <cstdint>
#include <vector>
#include <map>
#include <utility>

#include <vulkan/vulkan_core.h>
#include "Vulkan/VkInstance.h"
#include "Vulkan/VkSurface.h"
#include "Config/RenderConfig.h"

namespace Sil {
	enum QueueType : std::uint8_t {
		Graphics,
		Presentation,
		Transfer,
		Compute,
	};

	class GraphicsDevice
	{
	public:
		GraphicsDevice(const VkInstance& instance, const VkSurface& surface, const RenderingFeatures& requiredFeatures);
		~GraphicsDevice() 
		{
			vkDestroyDevice(_device, nullptr);
		}

		const VkDevice& GetDevice() const
		{
			return _device;
		}

		const VkPhysicalDevice& GetPhysicalDevice() const
		{
			return _physicalDevice;
		}

	private:
		VkPhysicalDevice _physicalDevice;
		VkDevice _device;

		const float _queuePriority = 1.f;
		std::vector<std::pair<QueueType, std::uint32_t>> _queueIndices;
		std::map<QueueType, VkQueue> _queueHandles;

		const VkDeviceQueueCreateInfo GetQueueCreateInfo(std::uint32_t queueIndex) const;

		void GetRequiredQueues(std::vector<VkDeviceQueueCreateInfo>& createInfo,
			const VkPhysicalDevice& device, const VkSurface& surface, const RenderingFeatures& requiredFeatures);
	};
}