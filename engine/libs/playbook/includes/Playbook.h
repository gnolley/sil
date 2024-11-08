#pragma once
#include "SilId.h"
#include "PlaybookConcepts.h"
#include "Asset.h"
#include "AssetLocation.h"
#include "AssetHandler.h"
#include "Assets/Shader.h"

#include <unordered_map>
#include <filesystem>

namespace Sil 
{
	class Playbook
	{
	public:

		static void IndexAssetsAtPath(const std::filesystem::path& path);
		
		template<AssetType TAsset>
		static const AssetToken<TAsset> LoadAssetFromID(SilId id)
		{
			if (_assetHandlers<TAsset>.contains(id))
			{
				auto handler = _assetHandlers<TAsset>.at(id);
				return handler.DistributeToken();
			}

			if (_indexedAssets.contains(id))
			{
				// Create asset processor
				// Create asset
				// Create handler
			}

			return AssetToken<TAsset>::InvalidToken();
		}

	private:
		static std::unordered_map<SilId, AssetLocation> _indexedAssets;

		template<AssetType TAsset> 
		static std::unordered_map<SilId, AssetHandler<TAsset>> _assetHandlers;
	};

	template<AssetType TAsset>
	std::unordered_map<SilId, AssetHandler<TAsset>> Playbook::_assetHandlers;
}