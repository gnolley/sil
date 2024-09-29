#include "SilEngine.h"
#include "Config.hpp"

#include <iostream>

int main()
{
	std::cout << "Bootstrapper: " << project_name << " Version " << project_version << ".\n";

	Sil::SilEngine engine{};
	engine.Run();

	return 0;
}