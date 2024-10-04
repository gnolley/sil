#pragma once

#include "vulkan/vulkan_core.h"
#include "Vulkan/VkInstance.h"

namespace Sil
{
	class VulkanDebugAdaptor
	{
	public:
		VulkanDebugAdaptor() = default;
		~VulkanDebugAdaptor();

		void EnableDebugger(const VkInstance& instance);
		void DisableDebugger();		

	private:
		const VkInstance* _instance;
		VkDebugUtilsMessengerEXT _messenger;

		static VKAPI_ATTR VkBool32 VKAPI_CALL CallbackMethod(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageTypes,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);
	};
}