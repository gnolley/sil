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
		AssetToken(const SilId& id, TAsset* asset, std::function<void(const SilId&)> releaseFunction)
			: _id(id), _asset(asset), _releaseToken(releaseFunction), _isValid(true)
		{
		}

		AssetToken()
			: _id(SilId::Empty()), _asset(nullptr), _releaseToken(std::nullopt), _isValid(false)
		{
		}

		// Moves token ownership, invalidates moved token
		AssetToken(const AssetToken&& other) noexcept
			: _id(other._id), _asset(other._asset), _releaseToken(other._releaseToken), _isValid(other._isValid)
		{
			other._isValid = false;
			other._releaseToken = std::nullopt;
		}

		// Never copy, only one token with this ID should exist.
		AssetToken(const AssetToken& other) = delete;

		~AssetToken()
		{
			if (_isValid && _releaseToken.has_value())
			{
				_releaseToken.value()(_id);
			}
		}

		static AssetToken InvalidToken()
		{
			return AssetToken();
		}

		const SilId& Id() const { return _id; }
		const TAsset* Asset() const { return _asset; }
		bool IsValid() const { return _isValid; }

	private:
		const SilId _id;
		const TAsset* _asset;

		std::optional<std::function<void(const SilId&)>> _releaseToken;
		bool _isValid;
	};
}