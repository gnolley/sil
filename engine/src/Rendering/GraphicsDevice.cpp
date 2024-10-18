#include "Rendering/GraphicsDevice.h"
#include "Vulkan/VkDeviceSelector.h"
#include "Debug/Logger.h"
#include <cassert>
#include <set>

std::vector<Sil::QueueType> GetRequiredQueueTypes(const Sil::RenderingFeatures& requiredFeatures);
const std::uint32_t GetPresentationQueueIndex(const std::vector<VkQueueFamilyProperties>& props, const VkPhysicalDevice& device, const VkSurfaceKHR& surface);
const std::uint32_t GetQueueIndex(const std::vector<VkQueueFamilyProperties>& props, Sil::QueueType queueType);
void PopulateQueueFamilyProperties(std::vector<VkQueueFamilyProperties>& props, const VkPhysicalDevice& device);

Sil::GraphicsDevice::GraphicsDevice(const VkInstance& instance, const VkSurface& surface,
	const RenderingFeatures& requiredFeatures)
	: _physicalDevice(VkDeviceSelector::SelectDevice(instance, surface, requiredFeatures)), _queueIndices(), _queueHandles()
{
	std::vector<VkDeviceQueueCreateInfo> queues{};
	GetRequiredQueues(queues, _physicalDevice, surface, requiredFeatures);

	VkPhysicalDeviceFeatures features{}; // TODO: create required features from feature list.
	const char* extensions = requiredFeatures.RequiredDeviceExtensions.data()->data();

	VkDeviceCreateInfo info{};
	info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	info.queueCreateInfoCount = static_cast<std::uint32_t>(queues.size());
	info.pQueueCreateInfos = queues.data();
	info.enabledExtensionCount = static_cast<std::uint32_t>(requiredFeatures.RequiredDeviceExtensions.size());
	info.ppEnabledExtensionNames = &extensions;
	info.enabledLayerCount = 0; // TODO: specify device-only layers for backwards compatibility
	info.pEnabledFeatures = &features;

	auto result = vkCreateDevice(_physicalDevice, &info, nullptr, &_device);
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Error creating VkDevice!");
	}

	for (auto& pair : _queueIndices)
	{
		VkQueue handle;
		vkGetDeviceQueue(_device, pair.second, 0, &handle);
		_queueHandles.insert({ pair.first, handle });
	}

	LogInfo("Graphics Device Initialised");
}

void Sil::GraphicsDevice::GetRequiredQueues(std::vector<VkDeviceQueueCreateInfo>& createInfo,
	const VkPhysicalDevice& device, const VkSurface& surface, const RenderingFeatures& requiredFeatures)
{
	std::vector<QueueType> requiredQueues = GetRequiredQueueTypes(requiredFeatures);

	std::vector<VkQueueFamilyProperties> props{};
	PopulateQueueFamilyProperties(props, device);

	std::set<std::uint32_t> uniqueIndices{};

	for (auto& rq : requiredQueues)
	{
		std::uint32_t index;
		if (rq == QueueType::Presentation)
		{
			index = GetPresentationQueueIndex(props, _physicalDevice, surface.GetSurface());
		}
		else
		{
			index = GetQueueIndex(props, rq);
		}

		if (uniqueIndices.contains(index) == false)
		{
			auto& queue = GetQueueCreateInfo(index);
			createInfo.push_back(queue);
			uniqueIndices.insert(index);
		}
		
		_queueIndices.push_back({rq, index});
	}
}

void PopulateQueueFamilyProperties(std::vector<VkQueueFamilyProperties>& props, const VkPhysicalDevice& device)
{
	std::uint32_t numQueueFamilies;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &numQueueFamilies, nullptr);

	props.resize(static_cast<size_t>(numQueueFamilies));
	vkGetPhysicalDeviceQueueFamilyProperties(device, &numQueueFamilies, props.data());
}

const VkQueueFlags QueueTypeToFlag(Sil::QueueType queueType)
{
	switch (queueType)
	{
	case Sil::QueueType::Graphics:
		return VK_QUEUE_GRAPHICS_BIT;
	case Sil::QueueType::Transfer:
		return VK_QUEUE_TRANSFER_BIT;
	case Sil::QueueType::Compute:
		return VK_QUEUE_COMPUTE_BIT;
	}

	throw std::runtime_error("Unknown Queue Type to VkQueueFlag mapping!");
}

const VkDeviceQueueCreateInfo Sil::GraphicsDevice::GetQueueCreateInfo(std::uint32_t queueIndex) const
{
	VkDeviceQueueCreateInfo info{};
	info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	info.queueCount = 1; // TODO: Work out needed queue amount. 1 is fine for now.
	info.queueFamilyIndex = static_cast<std::uint32_t>(queueIndex);
	info.flags = 0; // used for protected memory
	info.pQueuePriorities = &_queuePriority;

	return info;
}

const std::uint32_t GetQueueIndex(const std::vector<VkQueueFamilyProperties>& props, Sil::QueueType queueType)
{
	auto flag = QueueTypeToFlag(queueType);

	for (size_t i = 0; i < props.size(); ++i)
	{
		if (props[i].queueFlags & flag)
		{
			return static_cast<std::uint32_t>(i);
		}
	}

	throw std::runtime_error("Cannot find supported queue tyoe for required queue!");
}

const std::uint32_t GetPresentationQueueIndex(const std::vector<VkQueueFamilyProperties>& props, const VkPhysicalDevice& device, const VkSurfaceKHR& surface)
{
	VkBool32 supported = false;
	for (std::int32_t i = 0; i < props.size(); ++i)
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &supported);

		if (supported)
		{
			return i;
		}
	}

	throw std::runtime_error("Cannot find a presentation queue!");
}

std::vector<Sil::QueueType> GetRequiredQueueTypes(const Sil::RenderingFeatures& requiredFeatures)
{
	std::vector<Sil::QueueType> requiredQueues{};

	if (requiredFeatures.Graphics)
	{
		requiredQueues.push_back(Sil::QueueType::Graphics);
	}

	if (requiredFeatures.Presentation)
	{
		requiredQueues.push_back(Sil::QueueType::Presentation);
	}

	if (requiredFeatures.Transfer)
	{
		requiredQueues.push_back(Sil::QueueType::Transfer);
	}

	if (requiredFeatures.Compute)
	{
		requiredQueues.push_back(Sil::QueueType::Compute);
	}

	assert(requiredQueues.size() > 0 && "Graphics device must have at least 1 queue to function");

	return requiredQueues;
}
