#include "Mezzanine.h"
#include "Debug/Logger.h"
#include <iostream>
#include <format>
#include <Archivist.h>
#include <memory>

namespace Sil
{
	Mezzanine::Mezzanine(const RenderConfig& config, const Window& window)
		: _graphicsContext(config, window), _colorPass(_graphicsContext)
	{
		LogInfo(std::format("Mezzanine Initialised. Extensions: {0}, Layers {1}",
			_graphicsContext.NumEnabledExtensions(), _graphicsContext.NumEnabledValidationLayers()));

		_locator = std::make_shared<GraphicsLocator>(_graphicsContext, _colorPass);
		ProjectArchivist.Archive<GraphicsLocator>(_locator);
	}

	void Mezzanine::DisplaySplashScreen()
	{

	}
}