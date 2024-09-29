#pragma once
#include <string>

#include <Vulkan/VkInstance.h>
#include "Config/EngineConfig.h"
#include "Config/AppConfig.h"

namespace Sil
{
	class Renderer
	{
	public:
		Renderer(const AppConfig appConfig, const EngineConfig engineConfig);
		void Cleanup();

	private:
		std::unique_ptr<VkInstance> _instance;
	};
}