#pragma once

#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>

#include "Types.h"
#include "Processors/ShaderProcessor.hpp"

namespace filesystem = std::filesystem;

namespace Stagehand
{
	const BuilderMap ConstructBuilderMap()
	{
		return
		{
			{".vert", VertexStreamBuilder},
			{".frag", FragmentStreamBuilder}
		};
	}

	const StreamBuilder SelectStreamBuilder(const filesystem::path& fileExtension, const BuilderMap builderMap)
	{
		std::string extension = fileExtension.string();
		if (builderMap.contains(extension))
		{
			return builderMap.at(extension);
		}

		return [&fileExtension](const filesystem::path& inputPath, const filesystem::path& outputDirectory) {
			std::cout << "No stream builder found for " << fileExtension << "!\n";

			auto outputPath(outputDirectory);
			outputPath.replace_filename(inputPath.filename());
			outputPath.replace_extension(inputPath.extension());

			return std::ofstream(outputPath);
		};
	}

	const StreamBuilder SelectStreamBuilder(const filesystem::path& fileExtension)
	{
		const auto builderMap = ConstructBuilderMap();
		return SelectStreamBuilder(fileExtension, builderMap);
	}
}