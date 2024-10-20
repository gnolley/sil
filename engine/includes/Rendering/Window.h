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

		/// <summary>
		/// Gets the width of the window in Screen Coordinates.
		/// </summary>
		inline std::uint32_t GetWidth() const { return _width; }

		/// <summary>
		/// Gets the height of the window in Screen Coordinates.
		/// </summary>
		inline std::uint32_t GetHeight() const { return _height; }
		
		/// <summary>
		/// Gets the widths of the window in pixels (taking DPI into account).
		/// </summary>
		inline std::uint32_t GetWidthPx() const { return _widthPx; }

		/// <summary>
		/// Gets the height of the window in pixels (taking DPI into account).
		/// </summary>
		/// <returns></returns>
		inline std::uint32_t GetHeightPx() const { return _heightPx; }

	private:
		// GLFW Cannot be smart pointer
		GLFWwindow* _window;
		std::uint32_t _width, _height;
		std::uint32_t _widthPx, _heightPx;
	};
}