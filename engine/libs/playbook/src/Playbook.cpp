#include "Playbook.h"

namespace Sil
{
	void Sil::Playbook::LoadBuiltinResources()
	{
	}

	Asset& Playbook::GetAssetById(SilId& id)
	{
		return _assets[id.ToString()[0]];
	}
}