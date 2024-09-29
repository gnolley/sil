#pragma once
#include "Rendering/Window.h"
#include "Rendering/Renderer.h"
#include "Config/EngineConfig.h"
#include "Config/AppConfig.h"

#include <cstdint>
#include <memory>
#include <string>

namespace Sil
{
	class SilEngine {
	public:
		SilEngine(const AppConfig appConfig, const EngineConfig engineConfig);
		void Run();

	private:
		std::unique_ptr<Window> _mainWindow;
		std::unique_ptr<Renderer> _mainRenderer;

		void CreateMainWindow(std::uint32_t mainWindowWidth, std::uint32_t mainWindowHeight, std::string applicationName);
		void InitVulkan(const AppConfig appConfig, const EngineConfig engineConfig);
		void MainLoop();
		void Cleanup();
	};
}