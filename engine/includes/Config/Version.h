#pragma once

#include <string>
#include <cstdint>
#include <format>

namespace Sil
{
	struct Version
	{
		Version(std::uint16_t major, std::uint16_t minor, std::uint16_t patch)
			: Major(major), Minor(minor), Patch(patch)
		{
		}

		std::uint16_t Major, Minor, Patch;
		std::string ToString() const
		{
			return std::format("{0}.{1}.{2}", Major, Minor, Patch);
		}
	};
}