#pragma once

#include "ProcessorData.h"
#include "Types.h"
#include "Processors/ShaderProcessor.hpp"

#include <fstream>
#include <functional>
#include <string_view>
#include <string>
#include <map>

namespace Stagehand
{
	const ProcessMap ConstructProcessMap()
	{
		return
		{
			{".vert", VertexProcessor},
			{".frag", FragmentProcessor}
		};
	}

	Processor SelectProcessor(const filesystem::path& fileExtension, const ProcessMap& processMap)
	{
		std::string extension = fileExtension.string();
		if (processMap.contains(extension))
		{
			return processMap.at(extension);
		}

		return [](ProcessorData& data) {
			std::cout << "No processor found for " << data.inputPath << "!\n";
		};
	}

	Processor SelectProcessor(const filesystem::path& fileExtension)
	{
		const auto processMap = ConstructProcessMap();
		return SelectProcessor(fileExtension, processMap);
	}
}