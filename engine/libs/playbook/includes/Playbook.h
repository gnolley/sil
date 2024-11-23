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
		static AssetToken<TAsset> LoadAssetFromID(SilId id)
		{
			if (_assetHandlers<TAsset>.contains(id))
			{
				auto& handler = _assetHandlers<TAsset>.at(id);
				return handler.DistributeToken();
			}

			if (_indexedAssets.contains(id))
			{
				auto processor = AssetProcessor<TAsset>();

				// Create asset
				if (auto result = processor.ProcessAsset(_indexedAssets.at(id)); result.Status == ProcessStatus::Success)
				{
					// Create handler
					_assetHandlers<TAsset>.emplace(std::pair<SilId, AssetHandler<TAsset>>{id, AssetHandler<TAsset>(result.Asset) });
					return _assetHandlers<TAsset>.at(id).DistributeToken();
				}

				return AssetToken<TAsset>::InvalidToken();
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