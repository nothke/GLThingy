#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
using namespace glm;

class Transform
{
public:
	Transform(const vec3 pos = vec3(), const vec3 rot = vec3(), const vec3 scale = vec3(1, 1, 1)) :
		m_pos(pos),
		m_rot(rot),
		m_scale(scale) {}

	inline mat4 GetModel() const
	{
		mat4 posMatrix = translate(m_pos);
		mat4 rotxMatrix = rotate(m_rot.x, vec3(1, 0, 0));
		mat4 rotxMatriy = rotate(m_rot.y, vec3(0, 1, 0));
		mat4 rotxMatriz = rotate(m_rot.z, vec3(0, 0, 1));
		mat4 scaleMatrix = scale(m_scale);

		mat4 rotMatrix = rotxMatrix * rotxMatriy * rotxMatriz;

		return posMatrix * rotMatrix * scaleMatrix;
	}

	inline vec3 GetPos() { return m_pos; };
	inline vec3 GetRot() { return m_rot; };
	inline vec3 GetScale() { return m_scale; };

private:
	vec3 m_pos;
	vec3 m_rot;
	vec3 m_scale;
};

