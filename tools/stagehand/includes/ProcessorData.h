#pragma once

#include <filesystem>
#include <fstream>

namespace Stagehand
{
	struct ProcessorData
	{
		std::filesystem::path inputPath;
		std::ofstream outputStream;
	};
}