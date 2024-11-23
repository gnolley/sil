#pragma once

#include <AssetToken.h>

#include "SilId.h"
#include "Rendering/GraphicsContext.h"
#include "Vulkan/VkPipelineLayout.h"
#include "Vulkan/VkGraphicsPipeline.h"
#include <vulkan/vulkan_core.h>

#include "ShaderStage.h"

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
		Subtractive,
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
		AssetToken<ShaderStage> _vertexShader;
		AssetToken<ShaderStage> _fragmentShader;
		VkGraphicsPipeline _pipeline;
	};
}
