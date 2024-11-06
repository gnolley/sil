#include <iostream>
#include <stdlib.h>

#include <string>
#include <string_view>

#include <filesystem>
#include <CLI/CLI.hpp>

#include <functional>

#include "AssetProcessors.hpp"  
#include "StreamBuilders.hpp"

namespace filesystem = std::filesystem;

namespace Stagehand
{

	void ProcessFile(const filesystem::path& source, const filesystem::path& output)
	{
		auto inputExtension = source.extension();
		auto streamBuilder = SelectExtProcess<StreamBuilder>(inputExtension);

		auto processData = ProcessorData{};
		processData.inputPath = source;
		processData.outputStream = streamBuilder(source, output);

		Processor processor = SelectExtProcess<Processor>(inputExtension);
		processor(processData);

		processData.outputStream.close();
	}

	void ProcessFile(const filesystem::path& source, const filesystem::path& output, const BuilderMap& builderMap, const ProcessMap& processMap)
	{
		auto inputExtension = source.extension();
		auto streamBuilder = SelectExtProcess<StreamBuilder>(inputExtension, builderMap);

		auto processData = ProcessorData{};
		processData.inputPath = source;
		processData.outputStream = streamBuilder(source, output);

		Processor processor = SelectExtProcess<Processor>(inputExtension, processMap);
		processor(processData);

		processData.outputStream.close();
	}

	void ProcessDirectory(const filesystem::path& directory, const filesystem::path& outputDirectory, bool recursive)
	{
		auto builderMap = GetFuncMap<StreamBuilder>();
		auto processorMap = GetFuncMap<Processor>();
		
		if (recursive)
		{

			for (const auto& entry : filesystem::recursive_directory_iterator(directory))
			{
				if (entry.is_regular_file())
				{
					ProcessFile(entry.path(), outputDirectory, builderMap, processorMap);
				}
			}
		}
	}


}

int main(int argc, char** argv)
{
	CLI::App app{ "Cook tooling for Soliloquy Engine." };
	argv = app.ensure_utf8(argv);

	std::string inputPath = "";
	app.add_option("-i,--input", inputPath, "The file or directory of the asset to be cooked.")->required();

	std::string outputPath = "";
	app.add_option("-o,--output", outputPath, "The output directory for the cooked asset")->required();

	CLI11_PARSE(app, argc, argv);

	filesystem::path output(outputPath);

	if (filesystem::exists(outputPath) == false)
	{
		if (output.has_extension() == true)
		{
			std::cerr << "Output must be a directory, not a file!" << outputPath << "\n";
			return EXIT_FAILURE;
		}

		filesystem::create_directory(output);
	}
	else if (filesystem::is_directory(outputPath) == false)
	{
		std::cerr << "Output must be a directory, not a file!";
		return EXIT_FAILURE;
	}

	filesystem::path input(inputPath);
	if (filesystem::exists(inputPath) == false)
	{
		std::cerr << "Cannot find input path " << inputPath << "\n";
		return EXIT_FAILURE;
	}

	std::cout << "Cooking assets from " << input << " to " << output << ".\n";

	try {

		if (filesystem::is_regular_file(input))
		{
			Stagehand::ProcessFile(input, output);
		}
		else if (filesystem::is_directory(input))
		{
			Stagehand::ProcessDirectory(input, output, true);
		}
		else
		{
			std::cerr << "Inavlid input type! Must be file or directory!";
			return EXIT_FAILURE;
		}
	}
	catch (std::exception e) {
		std::cerr << "Cook failed! " << e.what();
		return EXIT_FAILURE;
	}


	return EXIT_SUCCESS;
}