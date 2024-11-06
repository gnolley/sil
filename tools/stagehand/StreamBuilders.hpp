#pragma once

#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>

#include "Types.h"
#include "Templates.hpp"
#include "Processors/ShaderProcessor.hpp"

namespace filesystem = std::filesystem;

namespace Stagehand
{
	template<>
	BuilderMap GetFuncMap<StreamBuilder>()
	{
		return
		{
			{".vert", VertexStreamBuilder},
			{".frag", FragmentStreamBuilder}
		};
	}

	template<>
	StreamBuilder GetFallbackFunc<StreamBuilder>()
	{
		return [](const filesystem::path& inputPath, const filesystem::path& outputDirectory) 
		{
			auto outputPath(outputDirectory);
			outputPath.replace_filename(inputPath.filename());
			outputPath.replace_extension(inputPath.extension());

			return std::ofstream(outputPath);
		};
	}
}