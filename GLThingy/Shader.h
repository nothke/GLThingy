#pragma once

#include <string>
#include <GL\glew.h>

class Shader
{
public:
	Shader(const std::string& fileName);

	void Bind();

	virtual ~Shader();


private:
	static const unsigned int NUM_SHADERS = 2;

	static std::string LoadShader(const std::string& fileName);
	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
};

