#include "Rendering/Window.h"

Sil::Window::Window(const std::uint32_t& width, const std::uint32_t& height, const std::string_view name)
	: _width(width), _height(height)
{
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	_window = glfwCreateWindow(width, height, name.data(), nullptr, nullptr);
}

Sil::Window::~Window()
{
	glfwDestroyWindow(_window);
}

bool Sil::Window::ShouldWindowClose()
{
	return glfwWindowShouldClose(_window);
}
