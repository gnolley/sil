#pragma once

#include "Rendering/GraphicsDevice.h"
#include "Rendering/Window.h"
#include "Vulkan/VkSurface.h"
#include "Config/RenderingFeatures.h"

#include <vector>

namespace Sil
{
	class Swapchain
	{
	public:
		Swapchain(const GraphicsDevice& device, const Window& window,
			const VkSurface& surface, const RenderingFeatures& requiredFeatures);
		~Swapchain();
	
		const VkSwapchainKHR& GetSwapchain() const
		{
			return _swapchain;
		}

	private:
		VkSwapchainKHR _swapchain;
		std::vector<VkImage> _images;

		const GraphicsDevice& _device;
		VkSurfaceCapabilitiesKHR _surfaceCapabilities;
		VkSurfaceFormatKHR _surfaceFormat;
		VkPresentModeKHR _presentMode;
	};
}