#include "Display.h"
#include <GL\glew.h>

Display::Display(int width, int height, const std::string& title)
{
	std::cout << "yo" << std::endl;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_DisplayMode current;
	SDL_GetDesktopDisplayMode(0, &current);

	float ddpi, hdpi, vdpi;
	auto noDpi = SDL_GetDisplayDPI(0, &ddpi, &hdpi, &vdpi);

	//width = current.w;
	//height = current.h;

	//width = 1920;
	//height = 1080;

	std::cout << current.w << " " << current.h << std::endl;

	if (noDpi != 0) SDL_Log("No dpi values");

	SDL_Log("Display: current display mode is %dx%dpx @ %dhz. ddpi: %d, hdpi: %d, vdpi: %d", current.w, current.h, current.refresh_rate, ddpi, hdpi, vdpi);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	//SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);

	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cerr << "Glew failed!" << std::endl;
	}

	isClosed = false;
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
	glClear(GL_COLOR_BUFFER_BIT);
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