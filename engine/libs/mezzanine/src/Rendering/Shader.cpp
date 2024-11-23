#include "Rendering/Shader.h"
#include "Mezzanine.h"
#include "Playbook.h"
#include "Rendering/ShaderStage.h"
#include <vulkan/vulkan_core.h>
#include <vector>
#include <cstdint>
#include <Archivist.h>

namespace Sil
{
	VkCullModeFlags GetCullMode(CullMode face)
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

	VkBlendOp GetBlendOp(BlendMode mode)
	{
		switch (mode)
		{
		case BlendMode::Additive:
			return VK_BLEND_OP_ADD;
		case BlendMode::Subtractive:
			return VK_BLEND_OP_SUBTRACT;
		case BlendMode::Min:
			return VK_BLEND_OP_MIN;
		case BlendMode::Max:
			return VK_BLEND_OP_MAX;
		}

		return VK_BLEND_OP_ADD;
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

	Shader::Shader(const ShaderState& state, const GraphicsContext& context)
		: _pipelineLayout(GetPipelineLayoutCreateInfo(), context.GetDevice()),
		_vertexShader(Playbook::LoadAssetFromID<ShaderStage>(state.VertexShaderId)),
		_fragmentShader(Playbook::LoadAssetFromID<ShaderStage>(state.FragmentShaderId)),
		_pipeline(context.GetDevice(), _pipelineLayout,
			std::initializer_list{_vertexShader.Asset(), _fragmentShader.Asset()},
			{state.EnableBlending, GetBlendOp(state.ColorBlend), GetBlendOp(state.AlphaBlend)},
			{GetCullMode(state.CullFace), 1.f})
	{
	}

	Shader::~Shader()
	{
	}
}