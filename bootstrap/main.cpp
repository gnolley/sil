#include "SilEngine.h"
#include "Config.hpp"
#include "Config/AppConfig.h"
#include "Config/EngineConfig.h"

#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main()
{
	std::cout << "Bootstrapper: " << project_name << " Version " << project_version << ".\n";

	const Sil::AppConfig appConfig(
		"Soliloquy Bootstrapper", 
		Sil::Version(1, 0, 0));

	const Sil::EngineConfig engineConfig(
		Sil::Version(project_version_major, project_version_minor, project_version_patch),
		800, 600
	);

	try {
		Sil::InitGraphicsContext();
		Sil::SilEngine engine(appConfig, engineConfig);
		engine.Run();
	}
	catch (const std::exception& err)
	{
		std::cerr << err.what() << "\n:";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}