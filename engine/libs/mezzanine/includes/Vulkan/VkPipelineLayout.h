#pragma once

#include <vulkan/vulkan_core.h>
#include "Rendering/GraphicsDevice.h"

namespace Sil
{
	class VkPipelineLayout
	{
	public:
		VkPipelineLayout(VkPipelineLayoutCreateInfo info, const GraphicsDevice& device)
			: _device(device)
		{
			if (vkCreatePipelineLayout(device.GetDevice(), &info, nullptr, &_pipelineLayout) != VK_SUCCESS)
			{
				throw std::runtime_error("Cannot create shader! Pipeline layout failed.");
			}
		}

		~VkPipelineLayout() 
		{
			vkDestroyPipelineLayout(_device.GetDevice(), _pipelineLayout, nullptr);
		}

		::VkPipelineLayout GetLayout() const { return _pipelineLayout; }

	private:
		::VkPipelineLayout _pipelineLayout;
		const GraphicsDevice& _device;
	};
}