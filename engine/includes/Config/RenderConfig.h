#pragma once

#include <string_view>
#include "Version.h"

namespace Sil
{
	struct RenderConfig {
		RenderConfig(std::string_view appName, const Version appVersion, const Version engineVersion)
			: AppName(appName), AppVersion(appVersion), EngineVersion(engineVersion)
		{
		}

		const std::string_view AppName;
		const Version AppVersion;
		const Version EngineVersion;
	};
}