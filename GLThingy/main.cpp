#include <iostream>
#include <GL/glew.h>
#include <Windows.h>

#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Hide console:
	//auto myConsole = GetConsoleWindow();
	//ShowWindow(myConsole, 0);

	cout << "Hello!" << endl;

	Display display(400, 300, "Hey, I drew a triangle in C++!");

	Shader shader(".\\res\\basicShader");
	Texture texture(".\\res\\rocket.png");

	Transform transform;

	float counter = 0;

	Vertex vertices[] = {
		Vertex(vec3(-0.5f, -0.5f, 0), vec2(0, 0)),
		Vertex(vec3(0, 0.5f, 0), vec2(0.5f, 1)),
		Vertex(vec3(0.5f, -0.5f, 0), vec2(1, 0))
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
	}

	return 0;
}