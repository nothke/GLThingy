#include "Shader.h"
#include <iostream>
#include <fstream>

static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string & fileName)
{
	// Create shader program
	m_program = glCreateProgram();

	// Load the shader
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	// Attach shaders to the program
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	// Pass vertex attributes
	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	// Errors
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Shader program failed to link: ");
	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Shader program is invalid: ");

	// Assign textures
	auto texLoc = glGetUniformLocation(m_program, "");
	glUniform1i(texLoc, 0);

	// Texture uniforms
	m_uniforms[DIFFUSE_MAP_U] = glGetUniformLocation(m_program, "diffuseMap");
	m_uniforms[BRDF_MAP_U] = glGetUniformLocation(m_program, "brdfMap");

	// Matrix uniforms
	m_uniforms[CAMERA_POSITION_U] = glGetUniformLocation(m_program, "cameraPosition");
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");

	std::cout << "Loaded vert/frag shader: " + fileName << std::endl;
}

void Shader::Bind()
{
	glUseProgram(m_program);

	glUniform1i(m_uniforms[DIFFUSE_MAP_U], 0);
	glUniform1i(m_uniforms[BRDF_MAP_U], 1);
}

void Shader::Update(const Transform & transform, const Camera & camera)
{
	mat4 model = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);

	glUniform3f(m_uniforms[CAMERA_POSITION_U],
		camera.position.x,
		camera.position.y,
		camera.position.z);
}


static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "Error: Shader creation failde" << std::endl;

	const GLchar* shaderSourceString[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceString[0] = text.c_str();
	shaderSourceStringLengths[0] == text.length();

	glShaderSource(shader, 1, shaderSourceString, shaderSourceStringLengths);
	glCompileShader(shader);

	//CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed");

	return shader;
}


std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}


Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);
}
