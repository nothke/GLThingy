#include "Display.h"
#include <GL\glew.h>

#define FULLSCREEN false

Display::Display(int width, int height, const std::string& title)
{
	std::cout << "yo" << std::endl;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_DisplayMode current;
	SDL_GetDesktopDisplayMode(0, &current);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	glEnable(GL_MULTISAMPLE);

	//width = current.w;
	//height = current.h;

	//width = 1920;
	//height = 1080;

	std::cout << current.w << " " << current.h << std::endl;

	SDL_Log("Display: current display mode is %dx%dpx @ %dhz.", current.w, current.h, current.refresh_rate);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (FULLSCREEN)
		SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);

	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cerr << "Glew failed!" << std::endl;
	}

	isClosed = false;

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();

	std::cout << "done" << std::endl;
}

void Display::Clear()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::ClearColorDontClearDepth(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_DEPTH_BUFFER_BIT);
}



bool Display::IsClosed()
{
	return isClosed;
}

void Display::Update()
{
	SDL_GL_SwapWindow(m_window);

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			isClosed = true;
	}
}