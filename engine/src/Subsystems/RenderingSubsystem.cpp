#include "Subsystems/RenderSubsystem.h"
#include "Debug/Logger.h"
#include <iostream>
#include <format>

Sil::RenderSubsystem::RenderSubsystem(const RenderConfig& config, const Window& window)
	: _graphicsContext(config, window)
{
	LogInfo(std::format("Render Subsystem Initialised. Extensions: {0}, Layers {1}",
		_graphicsContext.NumEnabledExtensions(), _graphicsContext.NumEnabledValidationLayers()));

	if (_graphicsContext.NumEnabledValidationLayers() > 0)
	{
		_debugAdaptor.EnableDebugger(_graphicsContext.GetVkInstance());
	}
}