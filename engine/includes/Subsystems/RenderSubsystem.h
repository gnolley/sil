#pragma once

#include "Config/RenderConfig.h"
#include "Rendering/Window.h"
#include "Rendering/GraphicsContext.h"
#include "Debug/VulkanDebugAdaptor.h"

namespace Sil
{
	class RenderSubsystem
	{
	public:
		RenderSubsystem(const RenderConfig& config, const Window& window);

	private:
		GraphicsContext _graphicsContext;
		VulkanDebugAdaptor _debugAdaptor {};
	};
}