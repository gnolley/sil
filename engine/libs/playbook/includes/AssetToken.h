#pragma once 

#include <functional>
#include "SilId.h"
#include "Asset.h"
#include "PlaybookConcepts.h"

namespace Sil
{
	template<AssetType TAsset>
	class AssetToken
	{
	public:
		AssetToken(SilId id, TAsset* asset, std::function<void(SilId)> releaseFunction)
			: _tokenId(id), Asset(asset), _releaseToken(releaseFunction)
		{
		}

		~AssetToken()
		{
			if (_isValid)
			{
				_releaseToken(_tokenId);
			}
		}

		const TAsset* const Asset;
		bool IsValid() const { return _isValid; }

		static AssetToken InvalidToken()
		{
			return
			{
				SilId::Empty(),
				nullptr,
				false
			};
		}

	private:
		const SilId _tokenId;
		const std::function<void(SilId)> _releaseToken;
		bool _isValid;
	};
}