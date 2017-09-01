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

		this->fov = fov;
		this->aspect = aspect;
		this->zNear = zNear;
		this->zFar = zFar;

		position = pos;
		forward = vec3(0, 0, 1);
		up = vec3(0, 1, 0);
	}

	inline void UpdateViewParameters()
	{
		m_perspective = perspective(fov, aspect, zNear, zFar);
	}

	inline mat4 GetViewProjection() const
	{
		return m_perspective * lookAt(position, position + forward, up);
	}

	vec3 position;
	vec3 forward;
	vec3 up;

	float fov;
	float aspect;
	float zNear;
	float zFar;

private:
	mat4 m_perspective;
};

