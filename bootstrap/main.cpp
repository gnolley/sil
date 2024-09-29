#include "SilEngine.h"
#include "Config.hpp"

#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main()
{
	std::cout << "Bootstrapper: " << project_name << " Version " << project_version << ".\n";

	try {
		Sil::SilEngine engine{};
		engine.Run();
	}
	catch (const std::exception& err)
	{
		std::cerr << err.what() << "\n:";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}