#pragma once

#include <vector>
#include <memory>

#include "Asset.h"
#include "AssetToken.h"
#include "PlaybookConcepts.h"

namespace Sil
{
	template<AssetType TAsset>
	class AssetHandler
	{
	public:

		AssetHandler(TAsset* asset) 
			: Asset(asset), Tokens{}
		{
		}

		const AssetToken<TAsset> DistributeToken()
		{
			return AssetToken
			{
				SilId::Empty(),
				OnTokenRelease(),
				true
			};
		}

	private:
		TAsset* Asset;
		std::vector<AssetToken<TAsset>> Tokens;

		void OnTokenRelease(SilId tokenId)
		{
			// do stuff
		}
	};
}