#include "Rendering/ShaderStage.h"
#include "vulkan/vulkan_core.h"
#include <stdint.h>
#include <format>

namespace Sil
{
	VkShaderModuleCreateInfo GetShaderModuleCreateInfo(const std::string_view byteCode)
	{
		auto info = VkShaderModuleCreateInfo{};
		info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		info.codeSize = byteCode.size();
		info.pCode = reinterpret_cast<const std::uint32_t*>(byteCode.data());

		return info;
	}

	VkShaderStageFlagBits StageTypeToVKStage(const StageType stageType)
	{
		switch (stageType)
		{
		case StageType::Vertex:
			return VK_SHADER_STAGE_VERTEX_BIT;

		case StageType::Fragment:
			return VK_SHADER_STAGE_FRAGMENT_BIT;
		}

		throw std::runtime_error(std::format("Cannot convert StageType {} to Vk Stage Bit!", static_cast<std::uint16_t>(stageType)));
	}

	ShaderStage::ShaderStage(const SilId& id, const StageType stageType, const GraphicsDevice& device, std::string_view byteCode)
	: Asset(id), _stageType(stageType), _shaderModule(GetShaderModuleCreateInfo(byteCode), device)
	{
	}

	VkPipelineShaderStageCreateInfo ShaderStage::GetPipelineStageCreateInfo() const
	{
		VkPipelineShaderStageCreateInfo info{};
		info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		info.stage = StageTypeToVKStage(_stageType);
		info.module = _shaderModule.GetModule();
		info.pSpecializationInfo = nullptr;

		return info;
	}
}