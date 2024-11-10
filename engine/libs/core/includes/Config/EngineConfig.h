#pragma once

#include <cstdint>
#include <filesystem>
#include "Version.h"

namespace Sil
{
	struct EngineConfig
	{
		EngineConfig(Version version, std::uint32_t mainWindowWidth, std::uint32_t mainWindowHeight, std::filesystem::path builtinAssetsPath)
			: EngineVersion(version), MainWindowWidth(mainWindowWidth), MainWindowHeight(mainWindowHeight), BuiltinAssetsRelativePath(builtinAssetsPath)
		{}

		Version EngineVersion;
		std::uint32_t MainWindowWidth, MainWindowHeight;
		std::filesystem::path BuiltinAssetsRelativePath;
	};
}