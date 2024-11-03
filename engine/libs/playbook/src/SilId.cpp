#include "SilId.h"
#include "xxhash.h"
#include <iostream>

const std::string_view Sil::SilId::ToString() const
{
	return "id";
	//return std::string_view(_id.begin(), _id.end());
}

Sil::SilId Sil::SilId::FromName(std::string_view nameToHash)
{
	//auto hash = XXH128()
	std::cout << nameToHash << "\n";
	return SilId();
}
