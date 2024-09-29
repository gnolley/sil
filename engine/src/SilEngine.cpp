#include "SilEngine.h"
#include <iostream>

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

Sil::SilEngine::SilEngine(const AppConfig appConfig, const EngineConfig engineConfig)
{
	std::cout << "Initialising Engine. Version: " << engineConfig.EngineVersion.ToString() << "\n";

	CreateMainWindow(engineConfig.MainWindowWidth, engineConfig.MainWindowHeight, appConfig.ApplicationName);
	InitVulkan(appConfig, engineConfig);

	// Initalise Sub Systems
}

// == Initialisation

void Sil::SilEngine::CreateMainWindow(std::uint32_t mainWindowWidth, std::uint32_t mainWindowHeight, std::string applicationName)
{
	// Create Window
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	_mainWindow = std::make_unique<Window>(mainWindowWidth, mainWindowHeight, applicationName);
}

void Sil::SilEngine::InitVulkan(const AppConfig appConfig, const EngineConfig engineConfig)
{
	_mainRenderer = std::make_unique<Renderer>(appConfig, engineConfig);
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
	while (_mainWindow->ShouldWindowClose() == false) {
		glfwPollEvents();
	}
}

void Sil::SilEngine::Cleanup()
{
	glfwTerminate();
}
