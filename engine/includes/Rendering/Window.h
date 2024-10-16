#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdint>
#include <string_view>

#include "Vulkan/VkInstance.h"

namespace Sil
{
	/// <summary>
	/// RAII Wrapper for GLFWwindow
	/// </summary>
	class Window
	{
	public:
		Window(const std::uint32_t& width, const std::uint32_t& height, const std::string_view name,
				const VkInstance& instance);
		~Window();

		bool ShouldWindowClose();
		bool WindowOpen() { return _window == nullptr; }

	private:
		// GLFW Cannot be smart pointer
		GLFWwindow* _window;
		std::uint32_t _width, _height;

		const VkInstance& _instance;
		VkSurfaceKHR _surface;
	};
}