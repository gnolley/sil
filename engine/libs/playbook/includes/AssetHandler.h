#pragma once

#include <vector>
#include <set>
#include <memory>
#include <iostream>

#include "Asset.h"
#include "AssetToken.h"
#include "PlaybookConcepts.h"
#include <algorithm>

namespace Sil
{
	template<AssetType TAsset>
	class AssetHandler
	{
		void OnTokenRelease(const SilId& tokenId)
		{
			for(auto it = _tokens.begin(); it != _tokens.end();)
			{
				if(*it == tokenId)
				{
					it = _tokens.erase(it);
				}
				else
				{
					++it;
				}
			}

			if(_tokens.empty())
			{
				// Proc destroy
			}
		}

	public:

		explicit AssetHandler(TAsset* asset)
			: _asset(asset)
		{
		}

		AssetToken<TAsset> DistributeToken()
		{
			SilId tokenId = SilId::NewId();
			_tokens.push_back(tokenId);
			return AssetToken<TAsset>(tokenId, nullptr, [&](const SilId& id) { OnTokenRelease(id); });
		}

	private:
		TAsset* _asset;
		std::vector<SilId> _tokens;
	};
}