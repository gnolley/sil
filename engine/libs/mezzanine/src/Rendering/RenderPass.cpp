#include "Rendering/RenderPass.h"
#include "Rendering/RenderTarget.h"

namespace Sil
{
	enum AttachmentType
	{
		Color,
		Depth,
	};

	void GetAttachment(const RenderTarget* target, AttachmentType attchmentType, VkAttachmentDescription& description, VkAttachmentReference& ref)
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
		ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	}

	VkRenderPassCreateInfo ConfigurePass(const GraphicsContext& context)
	{
		VkAttachmentDescription colorAttachment{};
		VkAttachmentReference attachmentRef{};
		auto& swapchain = context.GetSwapchain();
		GetAttachment(&swapchain, AttachmentType::Color, colorAttachment, attachmentRef);

		VkSubpassDescription subpassDescription{};
		subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpassDescription.inputAttachmentCount = 0;
		subpassDescription.pInputAttachments = nullptr;
		subpassDescription.colorAttachmentCount = 1;
		subpassDescription.pColorAttachments = &attachmentRef;

		// TODO: create a way to customise this.
		VkRenderPassCreateInfo info{};
		info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		info.attachmentCount = 1;
		info.pAttachments = &colorAttachment;
		info.subpassCount = 1;
		info.pSubpasses = &subpassDescription;

		return info;
	}

	RenderPass::RenderPass(const GraphicsContext& graphicsContext)
		: _renderPass(graphicsContext.GetDevice(), ConfigurePass(graphicsContext))
	{
	}
}