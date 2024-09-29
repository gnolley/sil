#include "SilEngine.h"
#include <iostream>

Sil::SilEngine::SilEngine()
{
	std::cout << "Initialising Engine. \n";
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
	// Create Window
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	_window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::cout << extensionCount << " extensions supported\n";
}

void Sil::SilEngine::MainLoop()
{
	while (!glfwWindowShouldClose(_window)) {
		glfwPollEvents();
	}
}

void Sil::SilEngine::Cleanup()
{
	glfwTerminate();
	glfwDestroyWindow(_window);
}
