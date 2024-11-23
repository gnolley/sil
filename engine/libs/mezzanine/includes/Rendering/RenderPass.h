#pragma once
#include "Vulkan/VkRenderPass.h"
#include "Rendering/GraphicsDevice.h"
#include "Rendering/GraphicsContext.h"

#include <vector>

namespace Sil
{
	class RenderPass {
	public:
		RenderPass(const GraphicsContext& graphicsContext);

		RenderPass(RenderPass& other) = delete;

		const VkRenderPass& GetHandle() const { return _renderPass; }
	private:

		VkRenderPassCreateInfo ConfigurePass(const GraphicsContext& context);

		std::vector<VkAttachmentDescription> _attachments;
		std::vector<VkAttachmentReference> _attachmentReferences;
		std::vector<VkSubpassDescription> _subpasses;

		VkRenderPass _renderPass;
	};
}