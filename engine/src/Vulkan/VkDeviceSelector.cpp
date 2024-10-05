#include "Vulkan/VkDeviceSelector.h"
#include <cstdint>
#include <vector>
#include <algorithm>

const VkPhysicalDevice Sil::VkDeviceSelector::SelectDevice(const VkInstance& instance)
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
	std::generate(ratedDevices.begin(), ratedDevices.end(), [device = devices.data()]() mutable {
		auto pair = std::pair<std::uint32_t, VkPhysicalDevice>{ CalculateDeviceHeuristic(*device), *device };
		++device;
		return pair;
	});

	// sort in descending order by rating
	std::sort(ratedDevices.begin(), ratedDevices.end(), [](auto& a, auto& b) {
		return a.first > b.first;
	});

	return ratedDevices[0].second;
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
