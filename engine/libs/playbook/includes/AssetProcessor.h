#pragma once

#include "PlaybookConcepts.h"
#include "AssetLocation.h"
#include <fstream>

namespace Sil
{
	enum ProcessStatus
	{
		Success,
		Failure,
		InvalidLocation,
		NoProcessor,
	};

	template<AssetType TAsset>
	struct ProcessResult
	{
		ProcessStatus Status;
		TAsset* Asset;
	};

	template<AssetType TAsset>
	class AssetProcessor
	{
	public:
		ProcessResult<TAsset> ProcessAsset(const AssetLocation& location)
		{
			return {
				ProcessStatus::NoProcessor,
				nullptr
			};
		}

	protected:
		std::ifstream CreateFileStream(const AssetLocation& location)
		{
			return std::ifstream(location.Path, std::ios::binary);
		}
	};
}