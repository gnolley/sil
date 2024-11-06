#pragma once

#include "Types.h"
#include "Templates.hpp"
#include "ProcessorData.h"
#include "Processors/ShaderProcessor.hpp"

#include <fstream>
#include <functional>
#include <string_view>
#include <string>

namespace Stagehand
{
	template<>
	ProcessMap GetFuncMap<Processor>()
	{
		return
		{
			{".vert", VertexProcessor},
			{".frag", FragmentProcessor}
		};
	}

	template<>
	Processor GetFallbackFunc<Processor>()
	{
		return [](ProcessorData& data) {
			std::cout << "No processor found for " << data.inputPath << "!\n";
		};
	}
}