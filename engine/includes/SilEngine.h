#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Sil
{
	class SilEngine {
	public:
		SilEngine();
		void Run();

	private:
		// GLFW Cannot be smart pointer
		GLFWwindow* _window;

		void InitVulkan();
		void MainLoop();
		void Cleanup();
	};
}