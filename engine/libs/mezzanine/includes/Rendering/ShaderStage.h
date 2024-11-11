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
		ShaderStage(SilId& id, StageType stageType, GraphicsDevice& device, std::string_view byteCode) : Asset(id);
		
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

			std::ifstream stream = CreateFileStream(location);
			std::stringstream ss();
			ss << stream.rdbuf();

			auto& device = Mezzanine::GetGraphicsDevice();
			shaderModule = new ShaderStage(device, ss.str());

			stream.close();

			return ProcessResult::Success;
		}
	};
}