#include "Rendering/Swapchain.h"
#include "Debug/Logger.h"
#include <format>
#include <stdexcept>
#include <algorithm>

void GetDeviceSurfacePresentationModes(std::vector<VkPresentModeKHR>& presentModes,
	const Sil::GraphicsDevice& device, const Sil::VkSurface& surface);
void GetSurfaceFormats(std::vector<VkSurfaceFormatKHR>& formats, 
	const Sil::GraphicsDevice& device, const Sil::VkSurface& surface);
const VkSurfaceFormatKHR ChooseColorFormat(const std::vector<VkSurfaceFormatKHR>& colorFormats);
const VkPresentModeKHR ChoosePresentMode(const std::vector<VkPresentModeKHR>& presentModes, const Sil::RenderingFeatures& requiredFeatures,
	const VkSurfaceCapabilitiesKHR& capabilities);
const VkExtent2D GetSwapchainExtent(const VkSurfaceCapabilitiesKHR& capabilities, const Sil::Window& window);
const std::uint32_t GetSwapchainImageCount(const VkSurfaceCapabilitiesKHR& capabilities, const Sil::RenderingFeatures& requiredFeatures);

Sil::Swapchain::Swapchain(const GraphicsDevice& device, const Window& window,
	const VkSurface& surface, const RenderingFeatures& requiredFeatures)
	:_device(device)
{
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device.GetPhysicalDevice(), surface.GetSurface(), &_surfaceCapabilities);

	std::vector<VkSurfaceFormatKHR> supportedFormats{};
	GetSurfaceFormats(supportedFormats, device, surface);

	std::vector<VkPresentModeKHR> presentModes{};
	GetDeviceSurfacePresentationModes(presentModes, device, surface);

	if (supportedFormats.empty() || presentModes.empty())
	{
		throw std::runtime_error("Cannot initialise swapchain! No supported formats or presentation modes!");
	}

	_surfaceFormat = ChooseColorFormat(supportedFormats);
	_presentMode = ChoosePresentMode(presentModes, requiredFeatures, _surfaceCapabilities);
	VkExtent2D extent = GetSwapchainExtent(_surfaceCapabilities, window);
	std::uint32_t imageCount = GetSwapchainImageCount(_surfaceCapabilities, requiredFeatures);

	const RenderQueue* graphicsQueue = device.GetQueue(QueueType::Graphics);
	const RenderQueue* presentQueue = device.GetQueue(QueueType::Presentation);
	std::vector<std::uint32_t> familyIndices{ graphicsQueue->QueueFamilyIndex, presentQueue->QueueFamilyIndex };

	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = surface.GetSurface();
	createInfo.imageFormat = _surfaceFormat.format;
	createInfo.imageColorSpace = _surfaceFormat.colorSpace;
	createInfo.presentMode = _presentMode;
	createInfo.imageExtent = extent;
	createInfo.minImageCount = imageCount;
	createInfo.imageArrayLayers = 1; // TODO: Support Stereoscopic?
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; // TODO: Support using swapchain as destination for HDR / Post Processing
	createInfo.preTransform = _surfaceCapabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE; // TODO: Handle swapchain recreation

	if (graphicsQueue->QueueFamilyIndex != presentQueue->QueueFamilyIndex)
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.pQueueFamilyIndices = familyIndices.data();
		createInfo.queueFamilyIndexCount = 2;
	}
	else
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}

	auto result = vkCreateSwapchainKHR(device.GetDevice(), &createInfo, nullptr, &_swapchain);
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Error creating swapchain!");
	}

	LogInfo("Swapchain Initialised");
}

Sil::Swapchain::~Swapchain()
{
	vkDestroySwapchainKHR(_device.GetDevice(), _swapchain, nullptr);
}

const std::uint32_t GetSwapchainImageCount(const VkSurfaceCapabilitiesKHR& capabilities, const Sil::RenderingFeatures& requiredFeatures)
{
	std::uint32_t desiredSwapchainCount = requiredFeatures.TrippleBuffering ? 3 : 2;
	if (capabilities.maxImageCount == 0 || capabilities.maxImageCount >= desiredSwapchainCount)
	{
		return desiredSwapchainCount;
	}

	Sil::LogWarning("Desired swapchain image count unsupported.");
	return capabilities.maxImageCount;
}

const VkExtent2D GetSwapchainExtent(const VkSurfaceCapabilitiesKHR& capabilities, const Sil::Window& window)
{
	return {
		std::clamp(window.GetWidthPx(), capabilities.minImageExtent.width, capabilities.maxImageExtent.width),
		std::clamp(window.GetHeightPx(), capabilities.minImageExtent.height, capabilities.maxImageExtent.height)
	};
}

const VkPresentModeKHR VSyncToPresentMode(Sil::VSyncMode vsyncMode)
{
	switch (vsyncMode)
	{
	case Sil::VSyncMode::Off: return VK_PRESENT_MODE_IMMEDIATE_KHR;
	case Sil::Relaxed: return VK_PRESENT_MODE_FIFO_RELAXED_KHR;
	case Sil::Capped: return VK_PRESENT_MODE_MAILBOX_KHR;
	default: return VK_PRESENT_MODE_FIFO_KHR;
	}
}

const VkPresentModeKHR ChoosePresentMode(const std::vector<VkPresentModeKHR>& presentModes, const Sil::RenderingFeatures& requiredFeatures,
	const VkSurfaceCapabilitiesKHR& capabilities)
{
	bool trippleBufferSupported = capabilities.maxImageCount == 0 || capabilities.maxImageCount >= 3;
	if (requiredFeatures.VSync == Sil::VSyncMode::Normal || (trippleBufferSupported == false && requiredFeatures.TrippleBuffering))
	{
		return VK_PRESENT_MODE_FIFO_KHR;
	}

	auto desiredMode = VSyncToPresentMode(requiredFeatures.VSync);
	for (auto& mode : presentModes)
	{
		if (mode == desiredMode)
		{
			return mode;
		}
	}

	Sil::LogWarning("VSync present mode unsupported. Defaulting to normal");
	return VK_PRESENT_MODE_FIFO_KHR;
}

const VkSurfaceFormatKHR ChooseColorFormat(const std::vector<VkSurfaceFormatKHR>& colorFormats)
{
	// TODO: Make more flexable, support finding more types.
	VkFormat desiredFormat = VK_FORMAT_B8G8R8A8_SRGB;
	VkColorSpaceKHR desiredColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;

	for (auto& format : colorFormats)
	{
		if (format.format == desiredFormat && format.colorSpace == desiredColorSpace)
		{
			return format;
		}
	}

	// First fallback -- try to match against color space

	for (auto& format : colorFormats)
	{
		if (format.colorSpace == desiredColorSpace)
		{
			return format;
		}
	}

	// last fallback, return first format.
	return colorFormats[0];
}

void GetDeviceSurfacePresentationModes(std::vector<VkPresentModeKHR>& presentModes,
	const Sil::GraphicsDevice& device, const Sil::VkSurface& surface)
{
	std::uint32_t modeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device.GetPhysicalDevice(), surface.GetSurface(), &modeCount, nullptr);

	presentModes.resize(modeCount);
	vkGetPhysicalDeviceSurfacePresentModesKHR(device.GetPhysicalDevice(), surface.GetSurface(), &modeCount, presentModes.data());
}

void GetSurfaceFormats(std::vector<VkSurfaceFormatKHR>& formats, const Sil::GraphicsDevice& device, const Sil::VkSurface& surface)
{
	std::uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device.GetPhysicalDevice(), surface.GetSurface(), &formatCount, nullptr);

	formats.resize(formatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(device.GetPhysicalDevice(), surface.GetSurface(), &formatCount, formats.data());
}