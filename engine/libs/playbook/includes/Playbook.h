#pragma once
#include "Asset.h"
#include "SilId.h"
#include <map>
#include <filesystem>

namespace Sil 
{
	class Playbook
	{
	public:

		void LoadBuiltinResources(const std::filesystem::path& path);
		Asset& GetAssetById(SilId& id);

	private:
		std::unordered_map<SilId, Asset> _assets;

	};
}