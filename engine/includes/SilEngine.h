#pragma once

#include "Subsystems/RenderSubsystem.h"
#include "Rendering/Window.h"
#include "Config/EngineConfig.h"
#include "Config/AppConfig.h"

#include <cstdint>
#include <memory>
#include <string>

namespace Sil
{
	void InitGraphicsContext();

	class SilEngine {
	public:

		SilEngine(const AppConfig& appConfig, const EngineConfig& engineConfig);
		void Run();

	private:
		Window _mainWindow;
		RenderSubsystem _renderSubsystem;

		void MainLoop();
		void Cleanup();
	};
}