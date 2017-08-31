#include <iostream>
#include <GL/glew.h>
#include <Windows.h>

#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

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

	Vertex vertices[] = {
		Vertex(vec3(-0.5f, -0.5f, -0.2f), vec2(0, 0)),
		Vertex(vec3(0, 0.5f, 0.2f), vec2(0.5f, 1)),
		Vertex(vec3(0.5f, -0.5f, 0.2f), vec2(1, 0))
	};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));


	while (!display.IsClosed())
	{
		display.Clear(0.867f, 0.627f, 0.867f, 1);

		shader.Bind();
		texture.Bind(0);
		mesh.Draw();

		display.Update();
	}

	return 0;
}