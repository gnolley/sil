#include "Playbook.h"
#include <iostream>
namespace filesystem = std::filesystem;

namespace Sil
{

	void Sil::Playbook::LoadBuiltinResources(const std::filesystem::path& path)
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
	}

	Asset& Playbook::GetAssetById(SilId& id)
	{
		return _assets[id];
	}
}