#pragma once

#include <iostream>
#include <string.h>
#include <GL\glew.h>

class Texture
{
public:
	Texture(const std::string& fileName);

	void Bind(unsigned int unit);

	virtual ~Texture();

private:

	GLuint m_texture;
};

