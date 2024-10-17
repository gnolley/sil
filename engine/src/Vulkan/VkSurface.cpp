#include "Vulkan/VkSurface.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

Sil::VkSurface::VkSurface(const VkInstance& instance, const Window& window)
	: _instance(instance)
{
	auto result = glfwCreateWindowSurface(_instance.GetInstance(), window.GetGLFWWindow(), nullptr, &_surface);
	if (result != VK_SUCCESS)
	{
		std::int32_t code = static_cast<std::int32_t>(result);
		throw std::runtime_error(std::format("Could not create window surface for rendering! Code {0}", code));
	}
}

Sil::VkSurface::~VkSurface()
{
	vkDestroySurfaceKHR(_instance.GetInstance(), _surface, nullptr);
}