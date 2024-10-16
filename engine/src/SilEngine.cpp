#include "SilEngine.h"
#include "Config/RenderConfig.h"
#include "Debug/Logger.h"

#include <iostream>
#include <cassert>
#include <format>

Sil::RenderConfig CreateRenderConfig(const Sil::AppConfig& appConfig, const Sil::EngineConfig& engineConfig)
{
	return Sil::RenderConfig(appConfig.ApplicationName, appConfig.AppVersion, engineConfig.EngineVersion, 
		Sil::RequiredRenderFeatures(true, false, false));
}

Sil::SilEngine::SilEngine(const AppConfig& appConfig, const EngineConfig& engineConfig)
	: _graphicsContext(CreateRenderConfig(appConfig, engineConfig)), 
		_mainWindow(engineConfig.MainWindowWidth, engineConfig.MainWindowHeight, appConfig.ApplicationName, _graphicsContext.GetVkInstance()),
		_renderSubsystem(_graphicsContext)
{
	LogMessage(std::format("Initialising Engine. {0}", engineConfig.EngineVersion.ToString()));
}

// == Runtime

void Sil::SilEngine::Run()
{
	LogMessage("Engine Running.");

	MainLoop();
	Cleanup();
}

void Sil::SilEngine::MainLoop()
{
	while (_mainWindow.ShouldWindowClose() == false) {
		_glfwInstance.PollEvents();
	}
}

void Sil::SilEngine::Cleanup()
{
}
