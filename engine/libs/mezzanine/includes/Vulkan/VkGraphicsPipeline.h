#pragma once
#include <vulkan/vulkan_core.h>

#include "Rendering/GraphicsDevice.h"
#include "Vulkan/VkPipelineLayout.h"
#include "Rendering/ShaderStage.h"

namespace Sil
{
	struct BlendInfo
	{
		bool Enabled = false;
		VkBlendOp ColorBlend = VK_BLEND_OP_ADD;
		VkBlendOp AlphaBlend = VK_BLEND_OP_ADD;
	};

	struct RasterizerInfo
	{
		VkCullModeFlags CullMode = VK_CULL_MODE_BACK_BIT;
		float DepthBias = 1.f;
	};

	class VkGraphicsPipeline
	{
	public:
		VkGraphicsPipeline(const GraphicsDevice& device, const VkPipelineLayout& layout, const std::vector<const ShaderStage*>& stages,
			BlendInfo blendInfo, RasterizerInfo rasterizerInfo);

	private:

		VkPipeline _pipeline { nullptr };
		const GraphicsDevice& _device;
	};
}
