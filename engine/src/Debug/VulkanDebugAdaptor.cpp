#include "Debug/VulkanDebugAdaptor.h"
#include "Debug/Logger.h"
#include <stdexcept>

const VkDebugUtilsMessageSeverityFlagBitsEXT MIN_MESSAGE_SEVERITY = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;

Sil::VulkanDebugAdaptor::VulkanDebugAdaptor(const VkInstance& instance)
{
	_instance = { &instance };

	VkDebugUtilsMessengerCreateInfoEXT createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity =
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

	createInfo.pfnUserCallback = CallbackMethod;

	auto pfn = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance.GetInstance(), "vkCreateDebugUtilsMessengerEXT");

	if (pfn == nullptr)
	{
		throw std::runtime_error("Debug utils extension not found.");
	}

	auto result = pfn(instance.GetInstance(), &createInfo, nullptr, &_messenger);

	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to set up debug messenger.");
	}

	LogInfo("Vulkan message debugger enabled");
}

Sil::VulkanDebugAdaptor::~VulkanDebugAdaptor() 
{
	auto pfn = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_instance.value()->GetInstance(), "vkDestroyDebugUtilsMessengerEXT");

	if (pfn != nullptr)
	{
		pfn(_instance.value()->GetInstance(), _messenger, nullptr);
	}
}	

#pragma warning(push)
#pragma warning(disable: 4100) // disable unused param warning, function definition comes from vulkan
VKAPI_ATTR VkBool32 VKAPI_CALL Sil::VulkanDebugAdaptor::CallbackMethod(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageTypes,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData)
#pragma warning(pop)
{
	if (messageSeverity < MIN_MESSAGE_SEVERITY)
	{
		return VK_FALSE;
	}

	Sil::Verbosity verbosity = Sil::Verbosity::Info;

	switch (messageSeverity)
	{
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
		verbosity = Warning;
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
		verbosity = Error;
		break;
	}

	Log(verbosity, pCallbackData->pMessage);

	return VK_FALSE;
}
