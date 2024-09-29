#include "SilEngine.h"
#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

Sil::SilEngine::SilEngine(std::uint32_t mainWindowWidth, std::uint32_t mainWindowHeight, std::string mainWindowName)
{
	std::cout << "Initialising Engine. \n";

	// Create Window
	glfwInit();
	_mainWindow = std::make_unique<Window>(mainWindowWidth, mainWindowHeight, mainWindowName);

	InitVulkan();

	// Initalise Sub Systems
}

void Sil::SilEngine::Run()
{
	std::cout << "Running Engine. \n";

	MainLoop();
	Cleanup();
}

void Sil::SilEngine::InitVulkan()
{
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::cout << extensionCount << " extensions supported\n";
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
