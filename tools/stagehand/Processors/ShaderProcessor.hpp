#pragma once

#include "Types.h"
#include "ProcessorData.h"
#include <shaderc/shaderc.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

#include <filesystem>

#include <string_view>
#include <string>

namespace filesystem = std::filesystem;

namespace Stagehand
{
	void GetShader(std::string& output, const filesystem::path& filePath)
	{
		std::ifstream fileStream(filePath);
		std::stringstream stringStream;

		stringStream << fileStream.rdbuf();

		fileStream.close();

		output = stringStream.str();
	}

	void CompileShader(std::string& output, const shaderc_shader_kind kind, const std::string& shader, const std::string& name)
	{
		const shaderc::Compiler compiler{};
		const shaderc::CompileOptions options{};

		auto preprocessResult = compiler.PreprocessGlsl(shader, kind, name.c_str(), options);
		if (preprocessResult.GetCompilationStatus() != shaderc_compilation_status_success)
		{
			throw std::runtime_error(std::format("Preprocessor failed on shader {}. Reason: {}", name, preprocessResult.GetErrorMessage()));
		}

		std::string shaderSource{ preprocessResult.begin(), preprocessResult.end() };

		auto compileResult = compiler.CompileGlslToSpv(shaderSource, shaderc_shader_kind::shaderc_glsl_default_vertex_shader, name.c_str(), options);
		if (compileResult.GetCompilationStatus() != shaderc_compilation_status_success)
		{
			throw std::runtime_error(std::format("Compiler failed on shader {}. Reason {}", name, compileResult.GetErrorMessage()));
		}

		output = std::string { compileResult.begin(), compileResult.end() };
	}

	inline void ShaderProcessor(ProcessorData& data, const shaderc_shader_kind kind)
	{
		std::string shaderRaw, shaderCompiled;
		GetShader(shaderRaw, data.inputPath);
		CompileShader(shaderCompiled, kind, shaderRaw, data.inputPath.filename().string());

		data.outputStream << shaderCompiled;
	}

	void VertexProcessor(ProcessorData& data)
	{
		return ShaderProcessor(data, shaderc_shader_kind::shaderc_vertex_shader);
	}

	void FragmentProcessor(ProcessorData& data)
	{
		return ShaderProcessor(data, shaderc_shader_kind::shaderc_fragment_shader);
	}


	inline std::ofstream ShaderStreamBuilder(const filesystem::path& inputPath, const filesystem::path& outputDirectory, const std::string_view suffix)
	{
		auto filename = inputPath.filename().stem();
		filename.concat(suffix);
		if (filesystem::is_directory(outputDirectory) == false)
		{
			throw std::runtime_error("Cannot create shader stream, output path is not directory!");
		}

		filesystem::path outputPath(outputDirectory);
		outputPath.append(filename.c_str());
		outputPath.replace_extension(".spv");

		return std::ofstream(outputPath, std::ios::binary);
	}

	std::ofstream VertexStreamBuilder(const filesystem::path& inputPath, const filesystem::path& outputDirectory)
	{
		return ShaderStreamBuilder(inputPath, outputDirectory, "_vert");
	}

	std::ofstream FragmentStreamBuilder(const filesystem::path& inputPath, const filesystem::path& outputDirectory)
	{
		return ShaderStreamBuilder(inputPath, outputDirectory, "_frag");
	}
}