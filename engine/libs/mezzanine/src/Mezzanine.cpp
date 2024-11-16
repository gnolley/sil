#include "Mezzanine.h"
#include "Debug/Logger.h"
#include <iostream>
#include <format>
#include <Archivist.h>
#include <memory>

namespace Sil
{
	const Mezzanine* Mezzanine::_instance;

	Mezzanine::Mezzanine(const RenderConfig& config, const Window& window)
		: _graphicsContext(config, window), _colorPass(_graphicsContext)
	{
		LogInfo(std::format("Mezzanine Initialised. Extensions: {0}, Layers {1}",
			_graphicsContext.NumEnabledExtensions(), _graphicsContext.NumEnabledValidationLayers()));

		if (_instance != nullptr)
		{
			LogError("Cannot setup multiple instances of Mezzanine!");
			return;
		}

		_instance = this;
		_locator = std::make_shared<GraphicsLocator>(_graphicsContext, _colorPass);
		ProjectArchivist.Archive<GraphicsLocator>(_locator);
	}

	void Mezzanine::DisplaySplashScreen()
	{

	}
}