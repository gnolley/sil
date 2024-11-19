#pragma once

#include "SilId.h"
#include "Rendering/GraphicsContext.h"
#include "Vulkan/VkPipelineLayout.h"
#include "Vulkan/VkGraphicsPipeline.h"
#include <vulkan/vulkan_core.h>

namespace Sil
{

	enum CullMode
	{
		None,
		Front,
		Back,
		Both,
	};

	enum BlendMode
	{
		Additive,
		Substractive,
		Min,
		Max,
	};

	struct ShaderState
	{
		SilId FragmentShaderId;
		SilId VertexShaderId;

		CullMode CullFace = CullMode::Back;
		bool EnableBlending = false;
		BlendMode ColorBlend = BlendMode::Additive;
		BlendMode AlphaBlend = BlendMode::Additive;
		float DepthBias = 0;
	};

	class Shader
	{
	public:
		Shader(const ShaderState& state, const GraphicsContext& context);
		~Shader();

	private:
		VkPipelineLayout _pipelineLayout;
		VkGraphicsPipeline _pipeline;
	};
}