#pragma once
#include <cstdint>
#include <vector>
#include <map>
#include <utility>

#include <vulkan/vulkan_core.h>
#include <Vulkan/VkInstance.h>
#include "Config/RenderConfig.h"

namespace Sil {
	enum QueueType : std::uint8_t {
		Graphics,
		Transfer,
		Compute,
	};

	class GraphicsDevice
	{
	public:
		GraphicsDevice(const VkInstance& instance, const RequiredRenderFeatures& requiredFeatures);
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

		const VkDeviceQueueCreateInfo GetQueue(const std::vector<VkQueueFamilyProperties>& props, Sil::QueueType queueType) const;

		void GetRequiredQueues(std::vector<VkDeviceQueueCreateInfo>& createInfo,
			const VkPhysicalDevice& device, const RequiredRenderFeatures& requiredFeatures);
	};
}