#include "Mesh.h"
#include <glm\vec3.hpp>
#include <vector>

#include "obj_loader.h"

using namespace glm;
using namespace std;



Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetUV());
	}

	for (unsigned int i = 0; i < numIndices; i++)
	{
		model.indices.push_back(indices[i]);
	}

	InitMesh(model);

	/*
	m_drawCount = numIndices;

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	vector<vec3> positions;
	vector<vec2> uvs;

	positions.reserve(numVertices);
	uvs.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; i++)
	{
		positions.push_back(*vertices[i].GetPos());
		uvs.push_back(*vertices[i].GetUV());
	}

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

	// POS
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// UV
	//unsigned int uvSize = numVertices * sizeof(uvs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(uvs[0]), &uvs[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// INDEX
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);


	glBindVertexArray(0);
	*/
}

Mesh::Mesh(const std::string & fileName)
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();


}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);

	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0); // last element? submesh offset?
	//glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::InitMesh(const IndexedModel & model)
{
	m_drawCount = model.indices.size();

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

	// POS
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// UV
	//unsigned int uvSize = numVertices * sizeof(uvs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// INDEX
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);


	glBindVertexArray(0);
}
