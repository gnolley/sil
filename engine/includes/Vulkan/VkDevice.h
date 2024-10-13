#pragma once
#include <vulkan/vulkan.h>
#include <stdexcept>

namespace Sil
{
	class VkDevice
	{
	public:
		VkDevice(const VkPhysicalDevice& phyicalDevice)
		{

		}

		VkDevice(const VkDevice&) = delete; // guard against deleting device with a copy.
		~VkDevice()
		{
		}

		const ::VkInstance& GetInstance() const { return _instance; }

	private:
		::VkInstance _instance;
	};
}