#include "Playbook.h"
#include "PlaybookConcepts.h"

#include <iostream>

namespace filesystem = std::filesystem;

namespace Sil
{
	std::unordered_map<SilId, AssetLocation> Playbook::_indexedAssets;

	void Playbook::IndexAssetsAtPath(const std::filesystem::path& path)
	{
		if (is_directory(path) == false)
		{
			throw std::runtime_error(std::format("Playbook cannot load directory {}, no such directory exists", path.string()));
		}

		for (auto& entry : filesystem::recursive_directory_iterator(path))
		{
			auto& p = entry.path();
			SilId id = SilId::FromName(p.filename().string());
			_indexedAssets.emplace(std::pair{ id, AssetLocation(id, p) });
		}
	}
}