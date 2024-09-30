#pragma once
#include <vulkan/vulkan.h>
#include <stdexcept>

namespace Sil
{
	class VkInstance
	{
	public:
		VkInstance(const VkInstanceCreateInfo createInfo)
		{
			auto result = vkCreateInstance(&createInfo, nullptr, &_instance);
			if (result != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create VkInstance.");
			}
		}

		VkInstance(const VkInstance&) = delete; // guard against deleting isntance with a copy.
		~VkInstance()
		{
			vkDestroyInstance(_instance, nullptr);
		}

	private:
		::VkInstance _instance;
	};
}