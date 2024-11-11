#pragma once

#include "PlaybookConcepts.h"
#include "AssetLocation.h"
#include <fstream>

namespace Sil
{
	enum ProcessResult
	{
		Success,
		Failure,
		InvalidLocation,
		NoProcessor,
	};

	template<AssetType TAsset>
	class AssetProcessor
	{
	public:
		ProcessResult ProcessAsset(const AssetLocation& location, TAsset* asset)
		{
			return ProcessResult::NoProcessor;
		}

	protected:
		std::ifstream CreateFileStream(const AssetLocation& location)
		{
			return std::ifstream(location.Path, std::ios::binary);
		}
	};
}