#include "SilId.h"

#define XXH_INLINE_ALL
#include "xxhash.h"

#include <iostream>
#include <stdint.h>
#include <sstream>

const XXH64_hash_t SEED = 1234;

//Note: It is assumed the data is 128-bits.

const std::string Sil::SilId::ToString() const
{
	std::stringstream ss;
	ss << std::hex;

	// Outputs 4 blocks of hexidecimal characters, seperated by a -
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			// need to widen the char, or it garbles the results
			ss << static_cast<std::uint16_t>(_id[4 * i + j]);
		}
		ss << "-";
	}

	for (int i = 12; i < 16; ++i)
	{
		// need to widen the char, or it garbles the results
		ss << static_cast<std::uint16_t>(_id[i]);
	}

	return ss.str();
}

Sil::SilId Sil::SilId::FromName(std::string_view nameToHash)
{
	SilId val{};

	auto hash = XXH128(nameToHash.data(), nameToHash.length(), SEED);
	std::uint64_t* lower = &hash.low64;

	// it is assumed that SilId holds a 128-bit char array.
	std::byte* iter = reinterpret_cast<std::byte*>(lower);
	for (int i = 0; i < 8; ++i)
	{
		val._id[i] = *iter;
		++iter;
	}

	std::uint64_t* upper = &hash.high64;
	iter = reinterpret_cast<std::byte*>(upper);
	for (int i = 8; i < 16; ++i)
	{
		val._id[i] = *iter;
		++iter;
	}

	return val;
}
