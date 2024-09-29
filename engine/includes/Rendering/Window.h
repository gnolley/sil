#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdint>
#include <string>

namespace Sil
{
	/// <summary>
	/// RAII Wrapper for GLFWwindow
	/// </summary>
	class Window
	{
	public:
		Window(std::uint32_t width, std::uint32_t height, std::string name);
		~Window();

		bool ShouldWindowClose();
		bool WindowOpen() { return _window == nullptr; }

	private:
		// GLFW Cannot be smart pointer
		GLFWwindow* _window;
		std::uint32_t _width, _height;
	};
}