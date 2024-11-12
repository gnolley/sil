#include "Mezzanine.h"
#include "Debug/Logger.h"
#include <iostream>
#include <format>

namespace Sil
{
	const Mezzanine* Mezzanine::_instance;

	Mezzanine::Mezzanine(const RenderConfig& config, const Window& window)
		: _graphicsContext(config, window)
	{
		LogInfo(std::format("Mezzanine Initialised. Extensions: {0}, Layers {1}",
			_graphicsContext.NumEnabledExtensions(), _graphicsContext.NumEnabledValidationLayers()));

		if (_instance != nullptr)
		{
			LogError("Cannot setup multiple instances of Mezzanine!");
			return;
		}

		_instance = this;
	}

	void Mezzanine::DisplaySplashScreen()
	{

	}

	const GraphicsDevice& Mezzanine::GetGraphicsDevice()
	{
		return _instance->_graphicsContext.GetDevice();
	}
}