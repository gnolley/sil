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

		const VkRenderPass& GetHandle() const { return _renderPass; }
	private:

		VkRenderPass _renderPass;
	};
}