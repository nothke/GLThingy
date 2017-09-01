#include <iostream>
#include <GL/glew.h>
#include <Windows.h>

#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

#define WIDTH 1280
#define HEIGHT 720

using namespace std;

int main(int argc, char* argv[])
{
	// Hide console:
	//auto myConsole = GetConsoleWindow();
	//ShowWindow(myConsole, 0);

	cout << "Hello!" << endl;

	Display display(WIDTH, HEIGHT, "Yup, *I AM* doing just fine");

	Shader shader(".\\res\\basicShader");
	Texture texture(".\\res\\stojadin_body_a.png");

	Camera camera(vec3(0, 0, -5), 70.0f, (float)WIDTH / HEIGHT, 0.2f, 1000);

	Transform transform;

	float counter = 0;

	//TRIANGLE
	/*
	Vertex vertices[] = {
		Vertex(vec3(-0.5f, -0.5f, 0), vec2(0, 0)),
		Vertex(vec3(0, 0.5f, 0), vec2(0.5f, 1)),
		Vertex(vec3(0.5f, -0.5f, 0), vec2(1, 0))
	};

	unsigned int indices[]{ 0, 1, 2 };
	*/

	//PYRAMID

	/*
	const float depth = 1;
	const float height = 0.7f;

	// NO NORMALS:

	Vertex vertices[] = {
		Vertex(vec3(-depth, -height, -depth), vec2(0, 0.2f)),
		Vertex(vec3(-depth, -height, depth), vec2(0, 1)),
		Vertex(vec3(depth, -height, depth), vec2(0.3f, 0)),
		Vertex(vec3(depth, -height, -depth), vec2(0, 1)),

		Vertex(vec3(0, height, 0), vec2(0.5f, 1)),
	};

	unsigned int indices[]{
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	*/

	Mesh mesh2(".\\res\\stojadin2.obj");

	/*
	float backDistance = 5;
	float backSize = 1;

	Vertex backVertices[] = {
		Vertex(vec3(-backSize, -backSize, backDistance), vec2(0, 0)),
		Vertex(vec3(-backSize, +backSize, backDistance), vec2(0, 1)),
		Vertex(vec3(+backSize, +backSize, backDistance), vec2(1, 1)),
		Vertex(vec3(+backSize, -backSize, backDistance), vec2(1, 0))
	};

	unsigned int backIndices[]{
		0, 1, 2,
		0, 2, 3
	};

	Mesh backMesh(backVertices, sizeof(backVertices) / sizeof(backVertices[0]),
		indices, sizeof(backIndices) / sizeof(backIndices[0]));
		*/

		// This was in while, but doesn't need to
	shader.Bind();
	texture.Bind(0);

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;

	while (!display.IsClosed())
	{
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = (double)((NOW - LAST) * 1000 / SDL_GetPerformanceFrequency());
		float dt = (float)deltaTime;

		/**Rendering**/

		display.Clear(0, 0, 0, 1);
		//display.Clear(0.9f, 0.427f, 0.9f, 1);

		shader.Update(transform, camera);

		//backMesh.Draw();
		mesh2.Draw();


		display.Update();

		counter += 0.001f;
		//transform.GetPos().x = sinf(counter);
		transform.GetRot().y = counter;
		transform.GetRot().z = counter * 0.3f;
	}

	return 0;
}

