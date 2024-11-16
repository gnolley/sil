#pragma once
#include <vulkan/vulkan_core.h>
#include "Rendering/GraphicsDevice.h"
#include <stdexcept>

namespace Sil
{
	class VkRenderPass
	{
	public:
		VkRenderPass(const GraphicsDevice& device, const VkRenderPassCreateInfo info)
			: _device(device)
		{
			if (vkCreateRenderPass(device.GetDevice(), &info, nullptr, &_renderPass) != VK_SUCCESS)
			{
				throw std::runtime_error("Renderpass creation failed!");
			}
		}

		~VkRenderPass()
		{
			vkDestroyRenderPass(_device.GetDevice(), _renderPass, nullptr);
		}

		const ::VkRenderPass& GetRenderPass() const { return _renderPass; }
	private:
		const GraphicsDevice& _device;
		::VkRenderPass _renderPass;
	};
}