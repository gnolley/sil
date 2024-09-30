#include "Subsystems/RenderSubsystem.h"

#include "Vulkan/VkInstance.h"
#include "Vulkan/VkUtils.h"

#include <iostream>

Sil::RenderSubsystem::RenderSubsystem(RenderConfig config)
	: _config(config), _appInfo(CreateAppInfo(config)), _instance(GetCreateInfo(_appInfo))
{
	std::cout << "Init Renderer" << "\n";
}