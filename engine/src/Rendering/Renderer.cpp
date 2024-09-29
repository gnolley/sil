#include "Rendering/Renderer.h"
#include <iostream>

Sil::Renderer::Renderer(const AppConfig appConfig, const EngineConfig engineConfig)
{
	std::cout << "Init Renderer. Config: \n App Name: " << appConfig.ApplicationName <<
		", Engine Version: " << engineConfig.EngineVersion.ToString() << "\n";
}