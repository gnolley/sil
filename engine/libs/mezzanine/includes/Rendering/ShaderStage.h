#pragma once
#include "AssetProcessor.h"
#include "Mezzanine.h"
#include "GraphicsDevice.h"
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
		
	private:
		VkShaderModule _shaderModule;
	};


	template<>
	class AssetProcessor<ShaderStage>
	{
		ProcessResult ProcessAsset(const AssetLocation& location, ShaderStage* shaderModule)
		{
			if (location.Path.extension() != ".spv")
			{
				return ProcessResult::InvalidLocation;
			}

			std::ifstream stream = location.GetFileStream();
			std::stringstream ss{};
			ss << stream.rdbuf();

			auto& device = Mezzanine::GetGraphicsDevice();
			shaderModule = new ShaderStage(location.AssetId, StageType::Vertex, device, ss.str());

			stream.close();

			return ProcessResult::Success;
		}
	};
}