#pragma once
#include "SilId.h"
#include <fstream>
#include <filesystem>

namespace Sil
{
	struct AssetLocation
	{
		AssetLocation(const SilId id, const std::filesystem::path path)
			: AssetId(id), Path(path)
		{}

		const SilId AssetId;
		const std::filesystem::path Path;

		std::ifstream GetFileStream() const
		{
			return std::ifstream(Path, std::ios::binary);
		}
	};
}