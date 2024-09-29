#include "Rendering/Window.h"

Sil::Window::Window(std::uint32_t width, std::uint32_t height, std::string name)
	: _width(width), _height(height)
{
	_window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
}

Sil::Window::~Window()
{
	glfwDestroyWindow(_window);
}

bool Sil::Window::ShouldWindowClose()
{
	return glfwWindowShouldClose(_window);
}
