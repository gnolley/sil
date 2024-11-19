#include "SilId.h"

#define XXH_INLINE_ALL
#include "xxhash.h"

#include <cstdint>
#include <sstream>
#include <random>

constexpr XXH64_hash_t SEED = 1234;

//Note: It is assumed the data is 128-bits
namespace Sil
{
	SilId::SilId(std::uint64_t a, std::uint64_t b)
	{
		_narrowId = a * b;

		// it is assumed that SilId holds a 128-bit char array.
		std::uint64_t* lower = &a;
		std::byte* iter = reinterpret_cast<std::byte*>(lower);
		for (int i = 0; i < 8; ++i)
		{
			_id[i] = *iter;
			++iter;
		}

		std::uint64_t* upper = &b;
		iter = reinterpret_cast<std::byte*>(upper);
		for (int i = 8; i < 16; ++i)
		{
			_id[i] = *iter;
			++iter;
		}
	}

	bool SilId::operator== (const SilId& other) const
	{
		for (int i = 0; i < 16; ++i)
		{
			if (_id[i] != other._id[i])
			{
				return false;
			}
		}

		return true;
	}

	const std::string SilId::ToString() const
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

	SilId Sil::SilId::NewId()
	{
		static std::random_device device;  // a seed source for the random number engine
		static std::mt19937_64 generator(device()); // mersenne_twister_engine seeded with rd()

		std::uniform_int_distribution<std::uint64_t> distribution(0, std::numeric_limits<std::uint64_t>::max());

		std::uint64_t lower = distribution(generator);
		std::uint64_t upper = distribution(generator);

		return SilId(lower, upper);
	}

	SilId Sil::SilId::FromName(std::string_view nameToHash)
	{
		auto hash = XXH128(nameToHash.data(), nameToHash.length(), SEED);
		return SilId(hash.low64, hash.high64);
	}
}