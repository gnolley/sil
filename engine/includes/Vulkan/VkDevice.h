#pragma once
#include <vulkan/vulkan.h>
#include <stdexcept>

namespace Sil
{
	class VkDevice
	{
	public:
		VkDevice(const VkPhysicalDevice& phyicalDevice)
			: _physicalDevice(phyicalDevice)
		{

		}

		VkDevice(const VkDevice&) = delete; // guard against deleting device with a copy.
		~VkDevice()
		{
		}

	private:
		const VkPhysicalDevice& _physicalDevice;
	};
}