#include "Config/RenderingFeatures.h"
#include <stdexcept>
#include <vulkan/vulkan_core.h>
#include "Debug/Logger.h"

Sil::RenderingFeatures& Sil::RenderingFeatures::UseGraphics(bool useGraphics, bool onScreenRendering)
{
	Graphics = useGraphics;
	Presentation = onScreenRendering;

	if (onScreenRendering == true && useGraphics == false)
	{
		throw std::runtime_error("Cannot perform on-screen rendering without rendering enabled!");
	}

	if (onScreenRendering)
	{
		RequiredDeviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	}

	return *this;
}

Sil::RenderingFeatures& Sil::RenderingFeatures::UseCompute(bool useCompute)
{
	Compute = useCompute;
	return *this;
}

Sil::RenderingFeatures& Sil::RenderingFeatures::UseAsyncDataTransfer(bool useTransfer)
{
	Transfer = useTransfer;
	return *this;
}

Sil::RenderingFeatures& Sil::RenderingFeatures::UsePresentation(VSyncMode vsync, bool trippleBuffer)
{
	TrippleBuffering = trippleBuffer;

	if (vsync == VSyncMode::Normal && trippleBuffer == false)
	{
		LogWarning("Uncapped Vsync mode requires tripple buffering!. Using Normal.");
		VSync = VSyncMode::Normal;
		return *this;
	}

	VSync = vsync;
	return *this;
}