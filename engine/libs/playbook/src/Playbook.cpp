#include "Playbook.h"
#include "PlaybookConcepts.h"

#include <iostream>

namespace filesystem = std::filesystem;

namespace Sil
{
	std::unordered_map<SilId, AssetLocation> Playbook::_indexedAssets;

	void Sil::Playbook::IndexAssetsAtPath(const std::filesystem::path& path)
	{
		if (filesystem::is_directory(path) == false)
		{
			throw std::runtime_error(std::format("Playbook cannot load directory {}, no such directory exists", path.string()));
		}

		for (auto& entry : filesystem::recursive_directory_iterator(path))
		{
			SilId id = SilId::FromName(path.filename().string());
			_indexedAssets.emplace(std::pair<SilId, AssetLocation>{ id, AssetLocation(id, path) });
		}
	}
}