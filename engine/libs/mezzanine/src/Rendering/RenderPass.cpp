#include "Rendering/RenderPass.h"
#include "Rendering/RenderTarget.h"

namespace Sil
{
	enum AttachmentType
	{
		Color,
		Depth,
	};

	VkImageLayout GetImageLayout(const AttachmentType type)
	{
		switch (type)
		{
			case Color:
				return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			case Depth:
				return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		}

		return VK_IMAGE_LAYOUT_UNDEFINED;
	}

	void GetAttachment(const RenderTarget* target, const AttachmentType attachmentType, VkAttachmentDescription& description, VkAttachmentReference& ref)
	{
		description.format = target->GetFormat();
		description.samples = VK_SAMPLE_COUNT_1_BIT;
		description.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
		description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		description.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		description.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		ref.attachment = 0;
		ref.layout = GetImageLayout(attachmentType);
	}

	VkRenderPassCreateInfo ConfigurePass(const GraphicsContext& context)
	{
		VkAttachmentDescription colorAttachment{};
		VkAttachmentReference attachmentRef{};
		auto& swapchain = context.GetSwapchain();
		GetAttachment(&swapchain, AttachmentType::Color, colorAttachment, attachmentRef);

		VkSubpassDescription subPassDescription{};
		subPassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subPassDescription.inputAttachmentCount = 0;
		subPassDescription.pInputAttachments = nullptr;
		subPassDescription.colorAttachmentCount = 1;
		subPassDescription.pColorAttachments = &attachmentRef;

		// TODO: create a way to customise this.
		VkRenderPassCreateInfo info{};
		info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		info.attachmentCount = 1;
		info.pAttachments = &colorAttachment;
		info.subpassCount = 1;
		info.pSubpasses = &subPassDescription;

		return info;
	}

	RenderPass::RenderPass(const GraphicsContext& graphicsContext)
		: _renderPass(graphicsContext.GetDevice(), ConfigurePass(graphicsContext))
	{
	}
}