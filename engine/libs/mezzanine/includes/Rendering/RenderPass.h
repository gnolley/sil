#pragma once
#include "Vulkan/VkRenderPass.h"
#include "Rendering/GraphicsDevice.h"
#include "Rendering/GraphicsContext.h"

namespace Sil
{
	class RenderPass {
	public:
		RenderPass(const GraphicsContext& graphicsContext);

		RenderPass(RenderPass& other) = delete;
	private:
		VkRenderPass _renderPass;
	};
}