#pragma once

#include "Asset.h"

namespace Sil
{
	class Shader : public Asset
	{
	public:
		Shader(SilId id) 
			: Asset(id)
		{
		}

	};
}