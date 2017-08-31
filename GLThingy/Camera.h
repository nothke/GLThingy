#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp> 

using namespace glm;

class Camera
{
public:
	Camera(const vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = perspective(fov, aspect, zNear, zFar);

		m_position = pos;
		m_forward = vec3(0, 0, 1);
		m_up = vec3(0, 1, 0);
	}

	inline mat4 GetViewProjection() const
	{
		return m_perspective * lookAt(m_position, m_position + m_forward, m_position + m_up);
	}

private:

	mat4 m_perspective;
	vec3 m_position;
	vec3 m_forward;
	vec3 m_up;
};

