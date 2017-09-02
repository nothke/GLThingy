#include <iostream>
#include <GL/glew.h>
#include <Windows.h>
#include <SDL2\SDL.h>

#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

#define WIDTH 1280
#define HEIGHT 720

using namespace std;

const float tickInterval = 1000.0f / 60.0f;

Uint32 TimeLeft()
{
	static Uint32 next_time = 0;

	Uint32 now;

	now = SDL_GetTicks();

	if (next_time <= now) {
		next_time = now + tickInterval;
		return 0;
	}

	return(next_time - now);
}

int main(int argc, char* argv[])
{
	// Hide console:
	//auto myConsole = GetConsoleWindow();
	//ShowWindow(myConsole, 0);

	Display display(WIDTH, HEIGHT, "Triangle -> 2.8 days later");

	display.Clear(0, 0, 0, 1);

	SDL_Delay(100);

	// LOAD SHADER AND TEXTURES
	Shader shader(".\\res\\basicShader");
	Texture texture(".\\res\\stojadin_body_a.png");
	Texture brickTexture(".\\res\\white.png");

	Texture brdfTexture(".\\res\\brdf4.png");

	Camera camera(vec3(0, 0, -5), 7000.0f, (float)WIDTH / HEIGHT, 1.0f, 1000);

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
	Mesh meshMonkey(".\\res\\diamond.obj");
	Mesh skysphere(".\\res\\skysphere.obj");

	// ASSIGN SHADER AND TEXTURES

	shader.Bind();

	brickTexture.Bind(0);
	brdfTexture.Bind(1);

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;

	float cameraZ = -4;
	float cameraZVelo = 0;

	int lastMouseX = 0;
	int lastMouseY = 0;

	float angle = 0;

	float fov = camera.fov / 100.0f;

	while (!display.IsClosed())
	{
		/**INPUT**/

		SDL_Event event;

		int mouseX = 0;
		int mouseY = 0;



		while (SDL_PollEvent(&event))
		{
			if (event.key.keysym.sym == SDLK_LEFT)
				cout << "LEFT!" << endl;

			if (event.key.keysym.sym == SDLK_UP)
			{
				fov += 1;
				cout << fov << endl;
			}

			if (event.key.keysym.sym == SDLK_DOWN)
			{
				fov -= 1;
				cout << fov << endl;
			}

			if (event.key.keysym.sym == SDLK_w)
			{
				if (event.type == SDL_KEYDOWN)
					cameraZVelo = 0.1f;
				else cameraZVelo = 0;
			}

			if (event.key.keysym.sym == SDLK_s)
			{
				if (event.type == SDL_KEYDOWN)
					cameraZVelo = -0.1f;
				else cameraZVelo = 0;
			}

			if (event.type == SDL_MOUSEMOTION)
			{
				mouseX = lastMouseX - event.motion.x;
				lastMouseX = event.motion.x;

				mouseY = lastMouseY - event.motion.y;
				lastMouseY = event.motion.y;

				angle = mouseX * 0.01f;

				//camera.m_position.x = cosf(angle) * 10;
				//camera.m_position.z = sinf(angle) * 10;

				//camera.m_position.x += mouseX * 0.1f;
				//camera.m_position.y += mouseY * 0.01f;
			}
		}

		cameraZ += cameraZVelo;

		/**Rendering**/

		display.Clear(0, 0, 0, 1);
		//display.Clear(0.9f, 0.427f, 0.9f, 1);

		shader.Update(transform, camera);

		meshMonkey.Draw();
		skysphere.Draw();

		display.Update();

		counter += 0.001f;
		//transform.GetPos().x = sinf(counter);
		transform.GetRot().y = counter * 10;
		//transform.GetRot().z = counter * 20;

		camera.position.z = cameraZ;

		camera.forward = -normalize(camera.position);

		camera.fov = fov / 100.0f;
		camera.UpdateViewParameters();

		SDL_Delay(TimeLeft());
	}

	return 0;
}

