#include "SilEngine.h"
#include "Config.hpp"

#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main()
{
	std::cout << "Bootstrapper: " << project_name << " Version " << project_version << ".\n";

	try {
		Sil::SilEngine engine(800, 600, std::string(project_name.data()));
		engine.Run();
	}
	catch (const std::exception& err)
	{
		std::cerr << err.what() << "\n:";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}