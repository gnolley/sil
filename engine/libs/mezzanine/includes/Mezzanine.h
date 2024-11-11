#pragma once

#include "Config/RenderConfig.h"
#include "Rendering/Window.h"
#include "Rendering/GraphicsContext.h"
#include "Debug/VulkanDebugAdaptor.h"

namespace Sil
{
	class Mezzanine
	{
	public:
		Mezzanine(const RenderConfig& config, const Window& window);
		void DisplaySplashScreen();

		static const GraphicsDevice& GetGraphicsDevice();
	private:
		GraphicsContext _graphicsContext;

		static const Mezzanine* _instance;
	};
}