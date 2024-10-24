#include <iostream>
#include <stdlib.h>

#include <shaderc/shaderc.hpp>
#include <fstream>
#include <sstream>
#include <string>

void GetShader(const std::string& filePath, std::string& shader)
{
	std::ifstream fileStream(filePath);
	std::stringstream stringStream;

	stringStream << fileStream.rdbuf();

	fileStream.close();

	shader = stringStream.str();
}

void CompileShader(std::string& output, const shaderc::Compiler& compiler, const shaderc_shader_kind kind, const std::string& shader, const std::string& name)
{
	const shaderc::CompileOptions options{};

	auto preprocessResult = compiler.PreprocessGlsl(shader, kind, name.c_str(), options);
	std::string preprocessed(preprocessResult.begin(), preprocessResult.end());

	auto compileResult = compiler.CompileGlslToSpv(preprocessed, shaderc_shader_kind::shaderc_glsl_default_vertex_shader, name.c_str(), options);
	if (compileResult.GetCompilationStatus() != shaderc_compilation_status::shaderc_compilation_status_success)
	{
		std::cout << "Error compiling shader " << name << ": " << compileResult.GetErrorMessage() << "\n";
	}
	output = { compileResult.begin(), compileResult.end() };
}

void WriteShader(std::string& compiledShader, std::string outputPath)
{
	std::ofstream output(outputPath, std::ios::binary);
	output << compiledShader;
	output.close();
}

int main()
{
	std::string vert, frag;
	GetShader("test.vert", vert);
	GetShader("test.frag", frag);

	shaderc::Compiler compiler{};
	std::string vertCompiled, fragCompiled;
	CompileShader(vertCompiled, compiler, shaderc_shader_kind::shaderc_glsl_vertex_shader, vert, "test");
	CompileShader(fragCompiled, compiler, shaderc_shader_kind::shaderc_fragment_shader, frag, "test");

	WriteShader(vertCompiled, "vert.spv");
	WriteShader(fragCompiled, "frag.spv");
	return EXIT_SUCCESS;

}