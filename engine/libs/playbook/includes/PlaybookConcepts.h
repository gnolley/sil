#pragma once
#include <type_traits>
#include "Asset.h"

namespace Sil
{
	template<typename TAsset>
	concept AssetType = std::is_base_of_v<Asset, TAsset>;
}