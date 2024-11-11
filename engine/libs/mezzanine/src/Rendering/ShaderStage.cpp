#include "Rendering/ShaderStage.h"
#include "vulkan/vulkan_core.h"
#include <stdint.h>
#include <format>

namespace Sil
{
	void CreateShaderModule(SilId& id, GraphicsDevice& device, std::string_view byteCode, VkShaderModule* shaderModule)
	{
		auto createInfo = VkShaderModuleCreateInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = byteCode.size();
		createInfo.pCode = reinterpret_cast<const std::uint32_t*>(byteCode.data());

		if (vkCreateShaderModule(device.GetDevice(), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
		{
			throw std::runtime_error(std::format("Failed to create shader module ", id.ToString()));
		}
	}

	VkShaderStageFlagBits StageTypeToVKStage(StageType stageType)
	{
		switch (stageType)
		{
		case StageType::Vertex:
			return VK_SHADER_STAGE_VERTEX_BIT;

		case StageType::Fragment:
			return VK_SHADER_STAGE_FRAGMENT_BIT;
		}

		throw new std::runtime_error(std::format("Cannot conver StageType {} to Vk Stage Bit!", stageType));
	}

	void CreateShaderStage(SilId& id, StageType stageType, GraphicsDevice& device, VkShaderModule& module)
	{
		VkPipelineShaderStageCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		createInfo.stage = StageTypeToVKStage(stageType);
		createInfo.module = module;
		createInfo.pSpecializationInfo = nullptr;
	}

	ShaderStage::ShaderStage(SilId& id, StageType stageType, GraphicsDevice& device, std::string_view byteCode) : Asset(id)
	{
		CreateShaderModule(id, device, byteCode, &_shaderModule);
		CreateShaderStage(id, stageType, device, _shaderModule);

		vkDestroyShaderModule(device.GetDevice(), _shaderModule, nullptr);
	}
}