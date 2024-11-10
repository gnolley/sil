#include "Rendering/Window.h"
#include <format>
#include <cstdlib>

Sil::Window::Window(const std::uint32_t& width, const std::uint32_t& height, const std::string_view name)
	: _width(width), _height(height), _widthPx(0), _heightPx(0)
{
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	_window = glfwCreateWindow(width, height, name.data(), nullptr, nullptr);

	int widthPx, heightPx;
	glfwGetFramebufferSize(_window, &widthPx, &heightPx);

	_widthPx = static_cast<std::uint32_t>(widthPx);
	_heightPx = static_cast<std::uint32_t>(heightPx);
}

Sil::Window::~Window()
{
	glfwDestroyWindow(_window);
}

bool Sil::Window::ShouldWindowClose()
{
	return glfwWindowShouldClose(_window);
}
