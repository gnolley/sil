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

	void GetAttachments(const RenderTarget* target, const AttachmentType attachmentType,
		std::vector<VkAttachmentDescription>& descriptions, std::vector<VkAttachmentReference>& refs)
	{
		descriptions = std::vector<VkAttachmentDescription>(1u);
		refs = std::vector<VkAttachmentReference>(1u);

		descriptions[0].format = target->GetFormat();
		descriptions[0].samples = VK_SAMPLE_COUNT_1_BIT;
		descriptions[0].loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
		descriptions[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		descriptions[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		descriptions[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		descriptions[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		descriptions[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		refs[0].attachment = 0;
		refs[0].layout = GetImageLayout(attachmentType);
	}

	VkRenderPassCreateInfo RenderPass::ConfigurePass(const GraphicsContext& context)
	{
		auto& swapchain = context.GetSwapchain();
		GetAttachments(&swapchain, AttachmentType::Color, _attachments, _attachmentReferences);

		_subpasses = std::vector<VkSubpassDescription>(1u);
		_subpasses[0].pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		_subpasses[0].colorAttachmentCount = _attachmentReferences.size();
		_subpasses[0].pColorAttachments = _attachmentReferences.data();

		// TODO: create a way to customise this.
		VkRenderPassCreateInfo info{};
		info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		info.attachmentCount = _attachments.size();
		info.subpassCount = _subpasses.size();
		info.pAttachments = _attachments.data();
		info.pSubpasses = _subpasses.data();

		return info;
	}

	RenderPass::RenderPass(const GraphicsContext& graphicsContext)
		: _renderPass(graphicsContext.GetDevice(), ConfigurePass(graphicsContext))
	{
	}
}