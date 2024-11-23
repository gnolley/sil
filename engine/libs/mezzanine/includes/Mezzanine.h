#pragma once

#include "Config/RenderConfig.h"
#include "Rendering/Window.h"
#include "Rendering/RenderPass.h"
#include "Rendering/GraphicsContext.h"
#include "Debug/VulkanDebugAdaptor.h"
#include "GraphicsLocator.h"

namespace Sil
{
	class Mezzanine
	{
	public:
		Mezzanine(const RenderConfig& config, const Window& window);
		void DisplaySplashScreen();

	private:
		GraphicsContext _graphicsContext;
		RenderPass _colorPass;
		std::shared_ptr<GraphicsLocator> _locator;
	};
}