#pragma once
#include <vulkan/vulkan_core.h>
#include "Rendering/GraphicsDevice.h"
#include <stdexcept>

namespace Sil
{
	class VkGraphicsPipeline
	{
	public:
		VkGraphicsPipeline(const VkGraphicsPipelineCreateInfo& info, const GraphicsDevice& device)
			: _device(device)
		{
			if (vkCreateGraphicsPipelines(device.GetDevice(), VK_NULL_HANDLE, 1u, &info, nullptr, &_pipeline)
				!= VK_SUCCESS)
			{
				throw std::runtime_error("Error while creating graphics pipeline!");
			}
		}
	private:
		VkPipeline _pipeline;
		const GraphicsDevice& _device;
	};
}