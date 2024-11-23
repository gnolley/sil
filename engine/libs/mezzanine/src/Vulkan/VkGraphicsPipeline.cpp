#include "Vulkan/VkGraphicsPipeline.h"
#include "GraphicsLocator.h"
#include "Archivist.h"

namespace Sil
{
    VkPipelineVertexInputStateCreateInfo GetVertextInputState()
	{
		VkPipelineVertexInputStateCreateInfo info{};
		info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		info.vertexBindingDescriptionCount = 0;
		info.pVertexBindingDescriptions = nullptr;
		info.vertexAttributeDescriptionCount = 0;
		info.pVertexAttributeDescriptions = nullptr;

		return info;
	}

	VkPipelineInputAssemblyStateCreateInfo GetInputAssemblyState()
	{
		VkPipelineInputAssemblyStateCreateInfo info{};
		info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		info.primitiveRestartEnable = VK_FALSE;
		info.topology = VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

		return info;
	}

	VkPipelineDynamicStateCreateInfo GetDynamicState(std::vector<VkDynamicState>& dynamicState)
	{
		dynamicState = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR
		};

		VkPipelineDynamicStateCreateInfo info{};
		info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		info.pDynamicStates = dynamicState.data();
		info.dynamicStateCount = static_cast<std::uint32_t>(dynamicState.size());

		return info;
	}

	VkPipelineViewportStateCreateInfo GetViewportStateCreateInfo()
	{
		VkPipelineViewportStateCreateInfo info{};
		info.scissorCount = 1;
		info.viewportCount = 1;

		return info;
	}

	VkPipelineMultisampleStateCreateInfo GetMultisampleStateCreateInfo()
	{
		VkPipelineMultisampleStateCreateInfo info{};
		info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		info.sampleShadingEnable = VK_FALSE;
		info.minSampleShading = 1;
		info.pSampleMask = nullptr;
		info.alphaToCoverageEnable = VK_FALSE;
		info.alphaToOneEnable = VK_FALSE;

		return info;
	}

	VkPipelineRasterizationStateCreateInfo GetRasterizationStateCreateInfo(RasterizerInfo rasterizerInfo)
	{
		VkPipelineRasterizationStateCreateInfo info{};
		info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		info.depthClampEnable = VK_FALSE;
		info.rasterizerDiscardEnable = VK_FALSE;
		info.polygonMode = VK_POLYGON_MODE_FILL;
		info.cullMode = rasterizerInfo.CullMode;
		info.frontFace = VK_FRONT_FACE_CLOCKWISE;
		info.depthBiasEnable = rasterizerInfo.DepthBias > 0.01f ? VK_TRUE : VK_FALSE;
		info.depthBiasConstantFactor = rasterizerInfo.DepthBias;
		info.depthBiasClamp = rasterizerInfo.DepthBias;
		info.depthBiasSlopeFactor = 0;

		return info;
	}

	VkPipelineColorBlendAttachmentState GetAttachmentBlendState(BlendInfo blendInfo)
	{
		VkPipelineColorBlendAttachmentState blendState{};
		blendState.colorBlendOp = blendInfo.ColorBlend;
		blendState.alphaBlendOp = blendInfo.AlphaBlend;
		blendState.blendEnable = blendInfo.Enabled;
		blendState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
			VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		blendState.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
		blendState.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
		blendState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		blendState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;

		return blendState;
	}

	VkPipelineColorBlendStateCreateInfo GetColorBlendState(const VkPipelineColorBlendAttachmentState* attachment)
	{
		VkPipelineColorBlendStateCreateInfo info{};
		info.logicOpEnable = VK_FALSE;
		info.logicOp = VK_LOGIC_OP_COPY;
		info.attachmentCount = 1u;
		info.pAttachments = attachment;
		info.blendConstants[0] = 0.f;
		info.blendConstants[1] = 0.f;
		info.blendConstants[2] = 0.f;
		info.blendConstants[3] = 0.f;

		return info;
	}

	void GetShaderStagesCreateInfos(const std::vector<const ShaderStage*>& stages, std::vector<VkPipelineShaderStageCreateInfo>& infos)
    {
    	infos = std::vector<VkPipelineShaderStageCreateInfo>{stages.size()};
	    for (size_t i = 0; i < stages.size(); ++i)
	    {
		    infos[i] = stages[i]->GetPipelineStageCreateInfo();
	    }
    }

	VkGraphicsPipeline::VkGraphicsPipeline(const GraphicsDevice& device, const VkPipelineLayout& layout,
		const std::vector<const ShaderStage*>& stages, BlendInfo blendInfo, RasterizerInfo rasterizerInfo)
			: _device(device)
	{
    	auto locator = ProjectArchivist.Retrieve<GraphicsLocator>();
    	const auto& colorPass = locator->GetColorPass();

    	std::vector<VkPipelineShaderStageCreateInfo> stageInfos{};
    	GetShaderStagesCreateInfos(stages, stageInfos);
    	auto vertexInputState = GetVertextInputState();
    	auto inputAssemblyState = GetInputAssemblyState();
    	auto viewportState = GetViewportStateCreateInfo();
    	auto rasterizationState = GetRasterizationStateCreateInfo(rasterizerInfo);
    	auto multisampleState = GetMultisampleStateCreateInfo();
    	auto attachmentBlendState = GetAttachmentBlendState(blendInfo);
    	auto colorBlendState = GetColorBlendState(&attachmentBlendState);
    	std::vector<VkDynamicState> dynamicStates{};
    	auto dynamicState = GetDynamicState(dynamicStates);

    	VkGraphicsPipelineCreateInfo info{};
    	info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    	info.stageCount = static_cast<std::uint32_t>(stages.size());
    	info.pStages = stageInfos.data();
    	info.pVertexInputState = &vertexInputState;
    	info.pInputAssemblyState = &inputAssemblyState;
    	info.pViewportState = &viewportState;
    	info.pRasterizationState = &rasterizationState;
    	info.pMultisampleState = &multisampleState;
    	info.pDepthStencilState = nullptr;
    	info.pColorBlendState = &colorBlendState;
    	info.pDynamicState = &dynamicState;
    	info.layout = layout.GetLayout();
    	info.renderPass = colorPass.GetHandle().GetRenderPass();
    	info.subpass = 0;
    	info.basePipelineHandle = VK_NULL_HANDLE;
    	info.basePipelineIndex = -1;

    	if (vkCreateGraphicsPipelines(device.GetDevice(), VK_NULL_HANDLE, 1u, &info, nullptr, &_pipeline)
			!= VK_SUCCESS)
    	{
    		throw std::runtime_error("Error while creating graphics pipeline!");
    	}
	}
}
