#include "Vulkan/VkDeviceSelector.h"
#include <cstdint>
#include <vector>
#include <algorithm>

const VkPhysicalDevice Sil::VkDeviceSelector::SelectDevice(const VkInstance& instance, const RequiredRenderFeatures& features)
{

	std::uint32_t numDevices;
	vkEnumeratePhysicalDevices(instance.GetInstance(), &numDevices, nullptr);

	if (numDevices == 0)
	{
		throw std::runtime_error("No Physical Devices Found!");
	}

	std::vector<VkPhysicalDevice> devices(numDevices);
	vkEnumeratePhysicalDevices(instance.GetInstance(), &numDevices, devices.data());

	std::vector<std::pair<std::uint32_t, VkPhysicalDevice>> ratedDevices(numDevices);
	for (auto& device : devices)
	{
		if (IsDeviceSupported(device, features) == false)
		{
			continue;
		}

		ratedDevices.push_back({ CalculateDeviceHeuristic(device), device });
	}

	// sort in descending order by rating
	std::sort(ratedDevices.begin(), ratedDevices.end(), [](auto& a, auto& b) {
		return a.first > b.first;
	});

	if (ratedDevices.size() == 0)
	{
		throw std::runtime_error("Physical hardware not supported!");
	}

	return ratedDevices[0].second;
}


const bool HasFlag(std::vector<VkQueueFamilyProperties>& props, VkQueueFlags bit)
{
	return std::any_of(props.begin(), props.end(), [&bit](auto& prop)
		{
			return (prop.queueFlags & bit) == bit;
		});
}


const bool Sil::VkDeviceSelector::IsDeviceSupported(VkPhysicalDevice& device, const RequiredRenderFeatures& features)
{
	std::uint32_t numQueueFamilies;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &numQueueFamilies, nullptr);

	std::vector<VkQueueFamilyProperties> props(numQueueFamilies);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &numQueueFamilies, props.data());

	if (features.Graphics && HasFlag(props, VK_QUEUE_GRAPHICS_BIT) == false)
	{
		return false;
	}

	if (features.Compute && HasFlag(props, VK_QUEUE_COMPUTE_BIT) == false)
	{
		return false;
	}

	if (features.Transfer && HasFlag(props, VK_QUEUE_TRANSFER_BIT) == false)
	{
		return false;
	}

	return true;
}


/// <summary>
/// Rates by device type, then total available local memory
/// I.e. A discrete GPU with 16GB of memory will have a rating of 1016,
/// while a integrated GPU with 4GB of memory would have a rating of 504
/// </summary>
const std::uint32_t Sil::VkDeviceSelector::CalculateDeviceHeuristic(VkPhysicalDevice& device)
{
	std::uint32_t rating = 0;
	VkPhysicalDeviceProperties props;

	vkGetPhysicalDeviceProperties(device, &props);

	switch (props.deviceType)
	{
	case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
		rating += 1000;
		break;

	case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
		rating += 500;
		break;

	case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
		rating += 250;
		break;
	}

	uint32_t totalAvailableMemoryGB{};
	VkPhysicalDeviceMemoryProperties memProps;
	vkGetPhysicalDeviceMemoryProperties(device, &memProps);

	const std::uint32_t numHeaps = memProps.memoryHeapCount;
	for (std::uint32_t i = 0; i < numHeaps; ++i)
	{
		auto heap = memProps.memoryHeaps[i];
		if ((heap.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) == VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
		{
			const std::uint64_t BytesPerGB = 1000000000;
			totalAvailableMemoryGB += static_cast<std::uint32_t>(heap.size / BytesPerGB);
		}
	}

	rating += totalAvailableMemoryGB;

	return rating;
}
