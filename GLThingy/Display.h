#pragma once

#include <iostream>
#include <SDL2\SDL.h>
//#undef main

class Display
{
public:
	Display(int width, int height, const std::string& title);
	~Display();

	void Clear();
	void Clear(float r, float g, float b, float a);
	void ClearColorDontClearDepth(float r, float g, float b, float a);

	void Update();

	bool IsClosed();

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	bool isClosed;
};

