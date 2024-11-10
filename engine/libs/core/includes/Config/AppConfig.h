#pragma once

#include <string_view>
#include "Version.h"

namespace Sil
{
	struct AppConfig
	{
		AppConfig(std::string_view appName, Version version)
			: ApplicationName(appName), AppVersion(version)
		{}

		std::string_view ApplicationName;
		Version AppVersion;
	};
}