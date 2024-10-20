#pragma once

#include <vulkan/vulkan_core.h>
#include <stdint.h>

namespace Sil
{
	struct RenderQueue
	{
	public:
		VkQueue Queue;
		std::uint32_t QueueFamilyIndex;
	};
}