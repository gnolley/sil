#pragma once
#include <cstdint>
#include <memory>
#include "Rendering/Window.h"
#include <string>

namespace Sil
{
	class SilEngine {
	public:
		SilEngine(std::uint32_t mainWindowWidth, std::uint32_t mainWindowHeight, std::string mainWindowName);
		void Run();

	private:
		std::unique_ptr<Window> _mainWindow;

		void InitVulkan();
		void MainLoop();
		void Cleanup();
	};
}