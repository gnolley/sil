#pragma once
#include <vulkan/vulkan_core.h>
#include <Debug/VulkanDebugAdaptor.h>
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

#if SIL_ENABLE_GFX_VALIDATION_LAYERS
			_debugAdaptor.EnableDebugger(&_instance);
#endif
		}

		VkInstance(const VkInstance&) = delete; // guard against deleting isntance with a copy.
		~VkInstance()
		{
			_debugAdaptor.DisableDebugger();
			vkDestroyInstance(_instance, nullptr);
		}

		const ::VkInstance& GetInstance() const { return _instance; }

	private:
		::VkInstance _instance;
		VulkanDebugAdaptor _debugAdaptor{};
	};
}