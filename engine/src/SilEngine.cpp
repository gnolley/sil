#include "SilEngine.h"
#include "Config/RenderConfig.h"
#include "Debug/Logger.h"

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cassert>
#include <format>

Sil::RenderConfig CreateRenderConfig(const Sil::AppConfig& appConfig, const Sil::EngineConfig& engineConfig)
{
	return Sil::RenderConfig(appConfig.ApplicationName, appConfig.AppVersion, engineConfig.EngineVersion);
}

Sil::SilEngine::SilEngine(const AppConfig& appConfig, const EngineConfig& engineConfig)
	: _mainWindow(engineConfig.MainWindowWidth, engineConfig.MainWindowHeight, appConfig.ApplicationName),
	  _renderSubsystem(CreateRenderConfig(appConfig, engineConfig))
{
	LogMessage(std::format("Initialising Engine. {0} \n", engineConfig.EngineVersion.ToString()));
}

void Sil::InitGraphicsContext()
{
	// Create Window
	auto result = glfwInit();
	assert(result == GLFW_TRUE);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

// == Runtime

void Sil::SilEngine::Run()
{
	LogMessage("Running.");

	MainLoop();
	Cleanup();
}

void Sil::SilEngine::MainLoop()
{
	while (_mainWindow.ShouldWindowClose() == false) {
		glfwPollEvents();
	}
}

void Sil::SilEngine::Cleanup()
{
	glfwTerminate(); 
}
