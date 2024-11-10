#pragma once
#include "SilId.h"
#include "Asset.h"
#include "AssetHandler.h"
#include "AssetLocation.h"
#include "AssetProcessor.h"
#include "PlaybookConcepts.h"

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
				auto& handler = _assetHandlers<TAsset>.at(id);
				return handler.DistributeToken();
			}

			if (_indexedAssets.contains(id))
			{
				auto processor = AssetProcessor<TAsset>();
				TAsset* asset;

				// Create asset
				if (processor.ProcessAsset(_indexedAssets.at(id), asset) != ProcessResult::Success)
				{
					return AssetToken<TAsset>::InvalidToken();
				}

				// Create handler
				_assetHandlers<TAsset>.emplace(std::pair<SilId, AssetHandler<TAsset>>{id, AssetHandler<TAsset>(asset) });
				return _assetHandlers<TAsset>.at(id).DistributeToken();
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