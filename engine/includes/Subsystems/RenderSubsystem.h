#pragma once

#include "Config/RenderConfig.h"
#include "Vulkan/VkInstance.h"

namespace Sil
{
	class RenderSubsystem
	{
	public:
		RenderSubsystem(RenderConfig config);

	private:
		RenderConfig _config;
		VkApplicationInfo _appInfo;
		VkInstance _instance;
	};
}