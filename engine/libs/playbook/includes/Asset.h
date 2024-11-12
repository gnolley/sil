#pragma once
#include "SilId.h"

namespace Sil
{
	class Asset
	{
	public:
		Asset(const SilId& id)
			: _id(id)
		{}
		
		const SilId& GetId() { return _id; }


	private:
		const SilId _id;
	};
}