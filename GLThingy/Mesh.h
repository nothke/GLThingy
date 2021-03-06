#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>
#include "obj_loader.h"

using namespace glm;

class Vertex
{
public:
	Vertex(const glm::vec3& pos, const vec2& uv, const vec3& normal)
	{
		this->pos = pos;
		this->uv = uv;
		this->normal = normal;
	}

	inline vec3* GetPos() { return &pos; };
	inline vec2* GetUV() { return &uv; };
	inline vec3* GetNormal() { return &normal; };

private:
	vec3 pos;
	vec2 uv;
	vec3 normal;
};

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

	Mesh(const std::string& fileName);

	void Draw();

	virtual ~Mesh();

private:

	void InitMesh(const IndexedModel& model);

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,

		INDEX_VB,

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};

