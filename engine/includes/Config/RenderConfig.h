#pragma once

#include <string_view>
#include <vector>
#include "Version.h"
#include <Config/RenderingFeatures.h>

namespace Sil
{
	struct RenderConfig {
		RenderConfig(std::string_view appName, const Version appVersion, const Version engineVersion, RenderingFeatures requiredFeatures)
			: AppName(appName), AppVersion(appVersion), EngineVersion(engineVersion), RequiredFeatures(requiredFeatures)
		{
		}

		const std::string_view AppName;
		const Version AppVersion;
		const Version EngineVersion;
		const RenderingFeatures RequiredFeatures;
	};


}