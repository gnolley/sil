#include "Rendering/GraphicsDevice.h"

const VkDeviceQueueCreateInfo GetQueue(const std::vector<VkQueueFamilyProperties>& props, Sil::QueueType queueType);

const std::vector<VkDeviceQueueCreateInfo> Sil::GraphicsDevice::GetRequiredQueues(
	const VkPhysicalDevice& device, const std::vector<QueueType>& requiredQueues) const
{
	std::uint32_t numQueueFamilies;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &numQueueFamilies, nullptr);

	std::vector<VkQueueFamilyProperties> props(numQueueFamilies);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &numQueueFamilies, props.data());

	std::vector<VkDeviceQueueCreateInfo> infos{};

	for (auto& rq : requiredQueues)
	{
		infos.push_back(GetQueue(props, rq));
	}

	return infos;
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

const VkDeviceQueueCreateInfo GetQueue(const std::vector<VkQueueFamilyProperties>& props, Sil::QueueType queueType)
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
			
			return info;
		}
	}

	throw std::runtime_error("Cannot find supported queue tyoe for required queue!");
}
