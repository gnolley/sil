#pragma once

#include "Config/RenderConfig.h"
#include "Vulkan/VkInstance.h"
#include "Rendering/GraphicsContext.h"
#include "Debug/VulkanDebugAdaptor.h"

namespace Sil
{
	class RenderSubsystem
	{
	public:
		RenderSubsystem(const GraphicsContext& context);

	private:
		const GraphicsContext& _context;
		VulkanDebugAdaptor _debugAdaptor {};
	};
}