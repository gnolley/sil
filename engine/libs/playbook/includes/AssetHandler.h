#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include "Asset.h"
#include "AssetToken.h"
#include "PlaybookConcepts.h"

namespace Sil
{
	template<AssetType TAsset>
	class AssetHandler
	{
		void OnTokenRelease(const SilId& tokenId)
		{
			// do shit =(
		}

	public:

		AssetHandler(TAsset* asset)
			: _asset(asset)
		{
		}

		const AssetToken<TAsset> DistributeToken()
		{
			SilId tokenId = SilId::NewId();
			
			auto token = AssetToken<TAsset>(tokenId, nullptr, [&](const SilId& id) { OnTokenRelease(id); });
			return token;
		}

	private:
		TAsset* _asset;
		std::vector<AssetToken<TAsset>> _tokens;

	};
}