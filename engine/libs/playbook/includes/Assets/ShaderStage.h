#pragma once
#include "AssetProcessor.h"

namespace Sil
{
	class ShaderStage : public Asset
	{

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

			shaderModule = new ShaderStage();

			stream.close();

			return ProcessResult::Success;
		}
	};
}