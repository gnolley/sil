#pragma once

#include "Rendering/GLFWInstance.h"
#include "Subsystems/RenderSubsystem.h"
#include "Rendering/GraphicsContext.h"
#include "Rendering/Window.h"
#include "Config/EngineConfig.h"
#include "Config/AppConfig.h"

#include <cstdint>
#include <memory>
#include <string>

namespace Sil
{
	class SilEngine {
	public:

		SilEngine(const AppConfig& appConfig, const EngineConfig& engineConfig);
		void Run();

	private:
		GLFWInstance _glfwInstance; // Must be before initialising graphics
		GraphicsContext _graphicsContext;
		Window _mainWindow;
		RenderSubsystem _renderSubsystem;

		void MainLoop();
		void Cleanup();
	};
}