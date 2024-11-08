#pragma once
#include "SilId.h"

namespace Sil
{
	class Asset
	{
	public:
		Asset(SilId id)
			: _id(id)
		{}
		
		const SilId& GetId() { return _id; }


	private:
		SilId _id;
	};
}