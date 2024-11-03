#pragma once
#include "Asset.h"
#include "SilId.h"
#include <map>

namespace Sil 
{
	class Playbook
	{
	public:

		void LoadBuiltinResources();
		Asset& GetAssetById(SilId& id);

	private:
		std::map<char, Asset> _assets;

	};
}