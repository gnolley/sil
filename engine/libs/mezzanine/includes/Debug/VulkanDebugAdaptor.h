#pragma once

#include "vulkan/vulkan_core.h"
#include "Vulkan/VkInstance.h"
#include <optional>

namespace Sil
{
	class VulkanDebugAdaptor
	{
	public:
		VulkanDebugAdaptor(const VkInstance& instance);
		~VulkanDebugAdaptor();

	private:
		std::optional<const VkInstance*> _instance = std::nullopt;
		VkDebugUtilsMessengerEXT _messenger;

		static VKAPI_ATTR VkBool32 VKAPI_CALL CallbackMethod(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageTypes,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);
	};
}