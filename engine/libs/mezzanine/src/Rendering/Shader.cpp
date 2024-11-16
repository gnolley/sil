#include "Rendering/Shader.h"
#include "Mezzanine.h"
#include "Playbook.h"
#include "Rendering/ShaderStage.h"
#include <vulkan/vulkan_core.h>
#include <vector>
#include <stdint.h>
#include <Archivist.h>

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

	VkCullModeFlagBits GetCullMode(CullMode face)
	{
		switch (face)
		{
		case CullMode::Front:
			return VK_CULL_MODE_FRONT_BIT;
		case CullMode::Back:
			return VK_CULL_MODE_BACK_BIT;
		case CullMode::None:
			return VK_CULL_MODE_NONE;
		case CullMode::Both:
			return VK_CULL_MODE_FRONT_AND_BACK;
		}

		return VK_CULL_MODE_BACK_BIT;
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

	VkPipelineRasterizationStateCreateInfo GetRasterizationStateCreateInfo(const ShaderState& state)
	{
		VkPipelineRasterizationStateCreateInfo info{};
		info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		info.depthClampEnable = VK_FALSE;
		info.rasterizerDiscardEnable = VK_FALSE;
		info.polygonMode = VK_POLYGON_MODE_FILL;
		info.cullMode = GetCullMode(state.CullFace);
		info.frontFace = VK_FRONT_FACE_CLOCKWISE;
		info.depthBiasEnable = state.DepthBias > 0.01f ? VK_TRUE : VK_FALSE;
		info.depthBiasConstantFactor = state.DepthBias;
		info.depthBiasClamp = state.DepthBias;
		info.depthBiasSlopeFactor = 0;

		return info;
	}

	VkBlendOp BlendModeToOp(BlendMode mode)
	{
		switch (mode)
		{
		case BlendMode::Additive:
			return VK_BLEND_OP_ADD;
		case BlendMode::Substractive:
			return VK_BLEND_OP_SUBTRACT;
		case BlendMode::Min:
			return VK_BLEND_OP_MIN;
		case BlendMode::Max:
			return VK_BLEND_OP_MAX;
		}

		return VK_BLEND_OP_ADD;
	}

	VkPipelineColorBlendAttachmentState GetAttachmentBlendState(const ShaderState& state)
	{
		VkPipelineColorBlendAttachmentState blendState{};
		blendState.colorBlendOp = BlendModeToOp(state.ColorBlend);
		blendState.alphaBlendOp = BlendModeToOp(state.AlphaBlend);
		blendState.blendEnable = state.EnableBlending;
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
	}

	VkPipelineLayoutCreateInfo GetPipelineLayoutCreateInfo()
	{
		// TODO: allow for uniforms to be set up in shader
		VkPipelineLayoutCreateInfo info{};
		info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		info.pSetLayouts = nullptr;
		info.setLayoutCount = 0;
		info.pPushConstantRanges = nullptr;
		info.pushConstantRangeCount = 0;

		return info;
	}

	void GetShaderStages(const ShaderState& state, std::vector<VkPipelineShaderStageCreateInfo>& stages)
	{
		AssetToken<ShaderStage> vertex = Playbook::LoadAssetFromID<ShaderStage>(state.VertexShaderId);
		AssetToken<ShaderStage> fragment = Playbook::LoadAssetFromID<ShaderStage>(state.FragmentShaderId);

		stages.push_back(vertex.Asset->GetPipelineStageCreateInfo());
		stages.push_back(fragment.Asset->GetPipelineStageCreateInfo());
	}

	VkGraphicsPipelineCreateInfo GetShaderPipelineInfo(const ShaderState& state, const VkPipelineLayout& layout)
	{
		auto locator = ProjectArchivist.Retreive<GraphicsLocator>();
		const auto& colorPass = locator->GetColorPass();

		std::vector<VkPipelineShaderStageCreateInfo> stages{};
		GetShaderStages(state, stages);
		auto vertexInputState = GetVertextInputState();
		auto inputAssemblyState = GetInputAssemblyState();
		auto viewportState = GetViewportStateCreateInfo();
		auto rasterizationState = GetRasterizationStateCreateInfo(state);
		auto multisampleState = GetMultisampleStateCreateInfo();
		auto attachmentBlendState = GetAttachmentBlendState(state);
		auto colorBlendState = GetColorBlendState(&attachmentBlendState);
		std::vector<VkDynamicState> dynamicStates{};
		auto dynamicState = GetDynamicState(dynamicStates);

		VkGraphicsPipelineCreateInfo info{};
		info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		info.stageCount = static_cast<std::uint32_t>(stages.size());
		info.pStages = stages.data();
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
	}

	Shader::Shader(const ShaderState& state, const GraphicsContext& context)
		: _pipelineLayout(GetPipelineLayoutCreateInfo(), context.GetDevice()), 
		  _pipeline(GetShaderPipelineInfo(state, _pipelineLayout), context.GetDevice())
	{		
		// TODO: Refactor to fix invalid mem issues when creating pipeline.
	}

	Shader::~Shader()
	{
	}
}