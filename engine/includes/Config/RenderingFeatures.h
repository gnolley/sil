#pragma once

#include <vector>
#include <string_view>
#include <stdint.h>

namespace Sil
{	
	enum VSyncMode : std::uint16_t
	{
		// Display frame immediately
		Off,
		// Display immediately if frame is late
		Relaxed,
		// Wait for vblank
		Capped,
		// Overwrite oldest buffer while waiting for vblank
		Normal
	};

	struct RenderingFeatures
	{
		RenderingFeatures& UseGraphics(bool useGraphics, bool onScreenRendering = true);
		RenderingFeatures& UseCompute(bool useCompute);
		RenderingFeatures& UseAsyncDataTransfer(bool useTransfer);
		RenderingFeatures& UsePresentation(VSyncMode vsync, bool trippleBuffer);

		/// <summary>
		/// Whether the renderer needs to output rendererd graphics.
		/// </summary>
		bool Graphics = true;

		/// <summary>
		/// Whether the renderer neeeds to support on-screen rendering.
		/// </summary>
		bool Presentation = true;

		/// <summary>
		/// Whether the renderer needs to support compute.
		/// </summary>
		bool Compute;

		/// <summary>
		/// Whether the renderer needs to support transfer queues.
		/// </summary>
		bool Transfer;

		/// <summary>
		/// Controls whether frames wait for vblank.
		/// </summary>
		VSyncMode VSync = VSyncMode::Normal;

		/// <summary>
		/// Use tripple buffering when able.
		/// </summary>
		bool TrippleBuffering = false;

		/// <summary>
		/// Which extensions are required on the device to function.
		/// </summary>
		std::vector<std::string_view> RequiredDeviceExtensions;
	};
}