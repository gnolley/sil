#pragma once
#include <vulkan/vulkan.h>

namespace Sil
{
	class VkInstance
	{
	public:
		VkInstance(std::string applicationName)
		{
			VkApplicationInfo appInfo{};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = applicationName;
			appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.pEngineName = "Soliloquy";
			appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
			appInfo.apiVersion = VK_API_VERSION_1_0;
		}

	private:
	};
}