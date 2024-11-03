#pragma once

#include <string_view>

namespace Sil
{
	class SilId
	{
	public:
		SilId() = default;
		//SilId(std::string_view id);

		const std::string_view ToString() const;

		//static SilId NewId();

		//// Hashes a name to a 128-bit id
		static SilId FromName(std::string_view nameToHash);

	private:
		char _id[16]; // 128-bit hash
	};
}