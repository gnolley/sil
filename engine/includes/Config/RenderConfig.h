#pragma once

#include <string_view>
#include <vector>
#include "Version.h"

namespace Sil
{
	struct RenderConfig {
		RenderConfig(std::string_view appName, const Version appVersion, const Version engineVersion,
			const std::vector<const char*> validationLayers)
			: AppName(appName), AppVersion(appVersion), EngineVersion(engineVersion),
			ValidationLayers(validationLayers)
		{
		}

		const std::string_view AppName;
		const Version AppVersion;
		const Version EngineVersion;
		const std::vector<const char *> ValidationLayers;
	};
}