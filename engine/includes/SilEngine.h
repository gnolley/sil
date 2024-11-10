#pragma once
#define GLFW_INCLUDE_VULKAN

#include "Config/EngineConfig.h"
#include "Config/AppConfig.h"

#include "Rendering/GLFWInstance.h"
#include "Rendering/Window.h"
#include "Mezzanine.h"
#include "Playbook.h"

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
		Window _mainWindow;
		Mezzanine _mezzanine;


		void MainLoop();
		void Cleanup();
	};
}