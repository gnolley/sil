#pragma once

#include <string>
#include "Version.h"

namespace Sil
{
	struct AppConfig
	{
		AppConfig(std::string appName, Version version)
			: ApplicationName(appName), AppVersion(version)
		{}

		std::string ApplicationName;
		Version AppVersion;
	};
}