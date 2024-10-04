#include "Subsystems/RenderSubsystem.h"
#include "Debug/Logger.h"
#include <iostream>
#include <format>

Sil::RenderSubsystem::RenderSubsystem(const GraphicsContext& context)
	: _context(context)
{
	LogInfo(std::format("Render Subsystem Initialised. Extensions: {0}, Layers {1}",
		_context.NumEnabledExtensions(), _context.NumEnabledValidationLayers()));

	if (context.NumEnabledValidationLayers() > 0)
	{
		_debugAdaptor.EnableDebugger(context.GetVkInstance());
	}
}