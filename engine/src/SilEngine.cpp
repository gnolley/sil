#include "SilEngine.h"
#include "Config/RenderConfig.h"
#include "Config/RenderingFeatures.h"
#include "Debug/Logger.h"

#include <iostream>
#include <cassert>
#include <format>

Sil::RenderConfig CreateRenderConfig(const Sil::AppConfig& appConfig, const Sil::EngineConfig& engineConfig)
{
	return Sil::RenderConfig(appConfig.ApplicationName, appConfig.AppVersion, engineConfig.EngineVersion, 
		Sil::RenderingFeatures(true, true, false, false));
}

Sil::SilEngine::SilEngine(const AppConfig& appConfig, const EngineConfig& engineConfig)
	: _glfwInstance(), _mainWindow(engineConfig.MainWindowWidth, engineConfig.MainWindowHeight, appConfig.ApplicationName),
		_renderSubsystem(CreateRenderConfig(appConfig, engineConfig), _mainWindow)
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
