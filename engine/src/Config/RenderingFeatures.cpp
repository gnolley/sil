#include "Config/RenderingFeatures.h"
#include <stdexcept>
#include <vulkan/vulkan_core.h>

Sil::RenderingFeatures::RenderingFeatures(bool rendering, bool onScreenRendering, bool compute, bool asyncMemoryTransfer)
	: Graphics(rendering), Presentation(onScreenRendering), Compute(compute), Transfer(asyncMemoryTransfer)
{
	if (onScreenRendering == true && rendering == false)
	{
		throw std::runtime_error("Cannot perform on-screen rendering without rendering enabled!");
	}

	if (onScreenRendering)
	{
		RequiredDeviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	}
}