#include "Rendering/GraphicsDevice.h"
#include "Vulkan/VkDeviceSelector.h"
#include "Debug/Logger.h"
#include <cassert>

std::vector<Sil::QueueType> GetRequiredQueueTypes(const Sil::RequiredRenderFeatures& requiredFeatures);

Sil::GraphicsDevice::GraphicsDevice(const VkInstance& instance, const RequiredRenderFeatures& requiredFeatures)
	: _physicalDevice(VkDeviceSelector::SelectDevice(instance, requiredFeatures)), _queueIndices(), _queueHandles()
{
	std::vector<VkDeviceQueueCreateInfo> queues{};
	GetRequiredQueues(queues, _physicalDevice, requiredFeatures);

	VkPhysicalDeviceFeatures features{}; // TODO: create required features from feature list.

	VkDeviceCreateInfo info{};
	info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	info.queueCreateInfoCount = static_cast<std::uint32_t>(queues.size());
	info.pQueueCreateInfos = queues.data();
	info.enabledExtensionCount = 0;
	info.enabledLayerCount = 0; // TODO: specify device-only layers for backwards compatibility

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
	const VkPhysicalDevice& device, const RequiredRenderFeatures& requiredFeatures)
{
	std::vector<QueueType> requiredQueues = GetRequiredQueueTypes(requiredFeatures);

	std::uint32_t numQueueFamilies;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &numQueueFamilies, nullptr);

	std::vector<VkQueueFamilyProperties> props(numQueueFamilies);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &numQueueFamilies, props.data());

	for (auto& rq : requiredQueues)
	{
		auto& queue = GetQueue(props, rq);
		createInfo.push_back(queue);
		_queueIndices.push_back({rq, queue.queueFamilyIndex});
	}
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

const VkDeviceQueueCreateInfo Sil::GraphicsDevice::GetQueue(const std::vector<VkQueueFamilyProperties>& props, Sil::QueueType queueType) const
{
	auto flag = QueueTypeToFlag(queueType);

	for (size_t i = 0; i < props.size(); ++i)
	{
		if (props[i].queueFlags & flag)
		{
			VkDeviceQueueCreateInfo info{};
			info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			info.queueCount = 1; // TODO: Work out needed queue amount. 1 is fine for now.
			info.queueFamilyIndex = static_cast<std::uint32_t>(i);
			info.flags = 0; // used for protected memory
			info.pQueuePriorities = &_queuePriority;
			
			return info;
		}
	}

	throw std::runtime_error("Cannot find supported queue tyoe for required queue!");
}

std::vector<Sil::QueueType> GetRequiredQueueTypes(const Sil::RequiredRenderFeatures& requiredFeatures)
{
	std::vector<Sil::QueueType> requiredQueues{};

	if (requiredFeatures.Graphics)
	{
		requiredQueues.push_back(Sil::QueueType::Graphics);
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
