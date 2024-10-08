#pragma once

#include <string_view>
#include <vector>
#include "Version.h"

namespace Sil
{
	struct RequiredRenderFeatures
	{
		RequiredRenderFeatures(bool graphics, bool compute, bool transfer)
			: Graphics(graphics), Compute(compute), Transfer(transfer)
		{
		}

		/// <summary>
		/// Whether the renderer needs to output rendererd graphics
		/// </summary>
		const bool Graphics = true;

		/// <summary>
		/// Whether the renderer needs to support compute
		/// </summary>
		const bool Compute;

		/// <summary>
		/// Whether the renderer needs to support transfer queues
		/// </summary>
		const bool Transfer;
	};


	struct RenderConfig {
		RenderConfig(std::string_view appName, const Version appVersion, const Version engineVersion, RequiredRenderFeatures requiredFeatures)
			: AppName(appName), AppVersion(appVersion), EngineVersion(engineVersion), RequiredFeatures(requiredFeatures)
		{
		}

		const std::string_view AppName;
		const Version AppVersion;
		const Version EngineVersion;
		const RequiredRenderFeatures RequiredFeatures;
	};


}