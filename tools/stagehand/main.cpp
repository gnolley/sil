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

int main()
{
	std::string vert, frag;
	GetShader("test.vert", vert);
	GetShader("test.frag", frag);

	shaderc::Compiler compiler{};
	shaderc::CompileOptions options{};

	auto preprocessResult = compiler.PreprocessGlsl(vert, shaderc_shader_kind::shaderc_glsl_vertex_shader, "vert", options);
	std::string preprocessed(preprocessResult.begin(), preprocessResult.end());

	auto compileResult = compiler.CompileGlslToSpv(preprocessed, shaderc_shader_kind::shaderc_glsl_default_vertex_shader, "vert", options);
	std::string shader (compileResult.begin(), compileResult.end());

	std::cout << "Compiled vert: \n" << shader;

	return EXIT_SUCCESS;

}