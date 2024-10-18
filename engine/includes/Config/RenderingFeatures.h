#pragma once

#include <vector>
#include <string_view>

namespace Sil
{	
	struct RenderingFeatures
	{
		RenderingFeatures(bool graphics, bool onScreenRendering, bool compute, bool asyncMemoryTransfer);

		/// <summary>
		/// Whether the renderer needs to output rendererd graphics
		/// </summary>
		const bool Graphics = true;

		/// <summary>
		/// Whether the renderer neeeds to support on-screen rendering.
		/// </summary>
		const bool Presentation = true;

		/// <summary>
		/// Whether the renderer needs to support compute
		/// </summary>
		const bool Compute;

		/// <summary>
		/// Whether the renderer needs to support transfer queues
		/// </summary>
		const bool Transfer;

		/// <summary>
		/// Which extensions are required on the device to function.
		/// </summary>
		std::vector<std::string_view> RequiredDeviceExtensions;
	};
}