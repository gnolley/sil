#include "Playbook.h"
#include <iostream>
#include "PlaybookConcepts.h"
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

		std::cout << "Loading Assets: ";
		for (auto& entry : filesystem::recursive_directory_iterator(path))
		{
			std::cout << entry.path().string() << ", ";
		}
		std::cout << "\n";

		auto id = SilId::FromName("SomeId");
		_assetHandlers<Shader>.emplace(std::pair<SilId, AssetHandler<Shader>>{ id, AssetHandler<Shader>((Shader*)nullptr)});
	}
}