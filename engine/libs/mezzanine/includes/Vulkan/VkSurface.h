#pragma once

#include "Vulkan/VkInstance.h"
#include "Rendering/Window.h"

#include <format>
#include <stdexcept>

namespace Sil
{
	class VkSurface
	{
	public:
		VkSurface(VkSurface& surface) = delete;
		VkSurface(const VkInstance& instance, const Window& window);
		~VkSurface();

		inline const VkSurfaceKHR& GetSurface() const { return _surface; }

	private:
		VkSurfaceKHR _surface;
		const VkInstance& _instance;
	};
}