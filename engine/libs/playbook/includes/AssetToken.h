#pragma once 

#include <functional>
#include <optional>
#include "SilId.h"
#include "Asset.h"
#include "PlaybookConcepts.h"

namespace Sil
{
	template<AssetType TAsset>
	class AssetToken
	{
	public:
		AssetToken(SilId id, TAsset* asset, std::function<void(const SilId&)> releaseFunction)
			: _id(id), PAsset(asset), _releaseToken(releaseFunction), _isValid(true)
		{
		}

		AssetToken()
			: _id(SilId::Empty()), PAsset(nullptr), _isValid(false)
		{
		}

		~AssetToken()
		{
			if (_isValid && _releaseToken.has_value())
			{
				_releaseToken.value()(_id);
			}
		}

		const TAsset* const Asset;
		bool IsValid() const { return _isValid; }

		static AssetToken InvalidToken()
		{
			return AssetToken();
		}

	private:
		const SilId _id;
		const std::optional<std::function<void(const SilId&)>> _releaseToken;
		bool _isValid;
	};
}