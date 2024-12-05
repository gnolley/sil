#pragma once
#include "AssetProcessor.h"
#include "GraphicsDevice.h"
#include "Archivist.h"
#include "GraphicsLocator.h"
#include "Vulkan/VkShaderModule.h"

#include <sstream>
#include <string_view>
#include <vulkan/vulkan_core.h>

namespace Sil
{
	enum StageType
	{
		Vertex,
		Fragment
	};

	class ShaderStage : public Asset
	{
	public:
		ShaderStage(const SilId& id, StageType stageType, const GraphicsDevice& device, std::string_view byteCode);
		VkPipelineShaderStageCreateInfo GetPipelineStageCreateInfo() const;

	private:
		StageType _stageType;
		VkShaderModule _shaderModule;
	};

	template<>
	class AssetProcessor<ShaderStage>
	{
	public:
		ProcessResult<ShaderStage> ProcessAsset(const AssetLocation& location)
		{
			if (location.Path.extension() != ".spv")
			{
				return
				{
					ProcessStatus::InvalidLocation,
					nullptr,
				};
			}

			std::ifstream stream = location.GetFileStream();
			std::stringstream ss{};
			ss << stream.rdbuf();

			auto locator = ProjectArchivist.Retrieve<GraphicsLocator>();
			auto& device = locator->GetContext().GetDevice();
			auto* stage = new ShaderStage(location.AssetId, Vertex, device, ss.str());

			stream.close();

			return
			{
				ProcessStatus::Success,
				stage,
			};

		}
	};
}