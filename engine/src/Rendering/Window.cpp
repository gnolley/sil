#include "Rendering/Window.h"
#include <format>
#include <cstdlib>

Sil::Window::Window(const std::uint32_t& width, const std::uint32_t& height, const std::string_view name,
	const VkInstance& instance)
	: _width(width), _height(height), _instance(instance)
{
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	_window = glfwCreateWindow(width, height, name.data(), nullptr, nullptr);

	auto result = glfwCreateWindowSurface(instance.GetInstance(), _window, nullptr, &_surface);
	if (result != VK_SUCCESS)
	{
		auto code = static_cast<std::int32_t>(result);
		throw std::runtime_error(std::format("Could not create window surface for rendering! Code {0}", code));
	}
}

Sil::Window::~Window()
{
	vkDestroySurfaceKHR(_instance.GetInstance(), _surface, nullptr);
	glfwDestroyWindow(_window);
}

bool Sil::Window::ShouldWindowClose()
{
	return glfwWindowShouldClose(_window);
}
