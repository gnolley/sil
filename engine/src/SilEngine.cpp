#include "SilEngine.h"
#include "Config/RenderConfig.h"

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cassert>

Sil::RenderConfig CreateRenderConfig(const Sil::AppConfig& appConfig, const Sil::EngineConfig& engineConfig)
{
	return Sil::RenderConfig(appConfig.ApplicationName, appConfig.AppVersion, engineConfig.EngineVersion);
}

Sil::SilEngine::SilEngine(const AppConfig& appConfig, const EngineConfig& engineConfig)
	: _mainWindow(engineConfig.MainWindowWidth, engineConfig.MainWindowHeight, appConfig.ApplicationName),
	  _renderSubsystem(CreateRenderConfig(appConfig, engineConfig))
{
	std::cout << "Initialising Engine. Version: " << engineConfig.EngineVersion.ToString() << "\n";
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
	std::cout << "Running Engine. \n";

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
