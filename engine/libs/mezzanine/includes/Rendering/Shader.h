#pragma once

#include "SilId.h"

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
		Shader(const ShaderState& state);
		~Shader();

	private:

	};
}