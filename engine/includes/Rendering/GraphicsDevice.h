#pragma once

namespace Sil {
	class GraphicsDevice
	{
	public:
		GraphicsDevice(VkPhysicalDevice& device, RequiredRenderFeatures requiredFeatures);

		const VkDevice& GetDevice() const;

	private:

		void GetCreateInfo(VkPhysicalDevice& device);
		void FindQueue(VkPhysicalDevice& device, QueueType queue) const;
	};
}