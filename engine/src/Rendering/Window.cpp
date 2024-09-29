#include "Rendering/Window.h"

Sil::Window::Window(std::uint32_t width, std::uint32_t height, std::string name)
{
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
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
