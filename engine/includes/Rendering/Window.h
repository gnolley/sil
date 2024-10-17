#pragma once

#include <GLFW/glfw3.h>

#include <cstdint>
#include <string_view>

namespace Sil
{
	/// <summary>
	/// RAII Wrapper for GLFWwindow
	/// </summary>
	class Window
	{
	public:
		Window(const std::uint32_t& width, const std::uint32_t& height, const std::string_view name);
		~Window();

		bool ShouldWindowClose();
		bool WindowOpen() { return _window == nullptr; }

		inline GLFWwindow* GetGLFWWindow() const { return _window; }

	private:
		// GLFW Cannot be smart pointer
		GLFWwindow* _window;
		std::uint32_t _width, _height;
	};
}