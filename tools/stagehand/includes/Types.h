#pragma once
#include <functional>
#include <filesystem>
#include <map>
#include "ProcessorData.h"

namespace Stagehand
{
	typedef std::function<void(ProcessorData&)> Processor;
	typedef std::map<std::string_view, Processor> ProcessMap;

	typedef std::function<std::ofstream(const std::filesystem::path&, const std::filesystem::path&)> StreamBuilder;
	typedef std::map<std::string_view, StreamBuilder> BuilderMap;
}