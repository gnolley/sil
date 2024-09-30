#pragma once

#include <cstdint>
#include "Version.h"

namespace Sil
{
	struct EngineConfig
	{
		EngineConfig(Version version, std::uint32_t mainWindowWidth, std::uint32_t mainWindowHeight)
			: EngineVersion(version), MainWindowWidth(mainWindowWidth), MainWindowHeight(mainWindowHeight)
		{}

		Version EngineVersion;
		std::uint32_t MainWindowWidth, MainWindowHeight;
	};
}