#include <iostream>
#include <GL/glew.h>
#include <Windows.h>

#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

#define WIDTH 800
#define HEIGHT 600

using namespace std;

Mesh Triangle()
{
	Vertex vertices[] = {
		Vertex(vec3(-0.5f, -0.5f, 0), vec2(0, 0)),
		Vertex(vec3(0, 0.5f, 0), vec2(0.5f, 1)),
		Vertex(vec3(0.5f, -0.5f, 0), vec2(1, 0))
	};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	return mesh;
}

Mesh* TrianglePtr()
{
	Vertex vertices[] = {
		Vertex(vec3(-0.5f, -0.5f, 0), vec2(0, 0)),
		Vertex(vec3(0, 0.5f, 0), vec2(0.5f, 1)),
		Vertex(vec3(0.5f, -0.5f, 0), vec2(1, 0))
	};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	return &mesh;
}

int main(int argc, char* argv[])
{
	// Hide console:
	//auto myConsole = GetConsoleWindow();
	//ShowWindow(myConsole, 0);

	cout << "Hello!" << endl;

	Display display(400, 300, "I'm doing just fine");

	Shader shader(".\\res\\basicShader");
	Texture texture(".\\res\\rocket.png");

	Camera camera(vec3(0, 0, -0.3f), 70.0f, (float)WIDTH / HEIGHT, 0.01f, 1000);

	Transform transform;

	float counter = 0;

	//TRIANGLE
	/*
	Vertex vertices[] = {
		Vertex(vec3(-0.5f, -0.5f, 0), vec2(0, 0)),
		Vertex(vec3(0, 0.5f, 0), vec2(0.5f, 1)),
		Vertex(vec3(0.5f, -0.5f, 0), vec2(1, 0))
	};*/

	//PYRAMID

	const float depth = 0.5f;
	const float height = 0.5f;

	Vertex vertices[] = {
		// FRONT
		Vertex(vec3(-depth, -height, -depth), vec2(0, 0)),
		Vertex(vec3(0, height, 0), vec2(0.5f, 1)),
		Vertex(vec3(depth, -height, -depth), vec2(1, 0)),

		// BACK
		Vertex(vec3(-depth, -height, depth), vec2(0, 0)),
		Vertex(vec3(0, height, 0), vec2(0.5f, 1)),
		Vertex(vec3(depth, -height, depth), vec2(1, 0)),

		Vertex(vec3(-depth, -height, -depth), vec2(0, 0)),
		Vertex(vec3(0, height, 0), vec2(0.5f, 1)),
		Vertex(vec3(-depth, -height, depth), vec2(1, 0)),

		Vertex(vec3(depth, -height * 2, -depth), vec2(0, 0)),
		Vertex(vec3(0, height, 0), vec2(0.5f, 1)),
		Vertex(vec3(depth, -height * 2, depth), vec2(1, 0)),
	};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

	// This was in while, but doesn't need to
	shader.Bind();
	texture.Bind(0);

	while (!display.IsClosed())
	{
		display.Clear(0.867f, 0.627f, 0.867f, 1);

		shader.Update(transform);

		mesh.Draw();

		display.Update();

		counter += 0.0001f;
		//transform.GetPos().x = sinf(counter);
		transform.GetRot().y = counter;
		transform.GetRot().z = counter * 2;
	}

	return 0;
}

