#include "Mezzanine.h"
#include "Debug/Logger.h"
#include <iostream>
#include <format>

namespace Sil
{
	Mezzanine::Mezzanine(const RenderConfig& config, const Window& window)
		: _graphicsContext(config, window)
	{
		LogInfo(std::format("Render Subsystem Initialised. Extensions: {0}, Layers {1}",
			_graphicsContext.NumEnabledExtensions(), _graphicsContext.NumEnabledValidationLayers()));
	}
}