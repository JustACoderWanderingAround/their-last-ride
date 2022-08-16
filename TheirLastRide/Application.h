#pragma once
#include "Scene.h"
#include "timer.h"
#define SDL_MAIN_HANDLED
#include <SDL.h>

class Application
{
private:
	float _targetFps;
	Timer _timer;
	SDL_Surface* _winSurface;
	SDL_Window* _window;
public:
	Application();
	void Init();
	void Run();
	void Exit();
	SDL_Window* getWindow() const;
	SDL_Surface* getWindowSurface() const;

	static bool IsKeyPressed(unsigned short key);
};

