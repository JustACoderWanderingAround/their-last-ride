#pragma once
#include "Scene.h"
#include "timer.h"
#include "Singleton.h"
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>

class Application : public Singleton<Application>
{
private:
	float _targetFps;
	Timer _timer;
	SDL_Surface* _winSurface;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Event _event;
public:
	Application();
	void Init();
	void Run();
	void Exit();
	void pause(long long time);
	SDL_Window* getWindow() const;
	SDL_Surface* getWindowSurface() const;
	SDL_Renderer* getRenderer() const;
	static bool IsKeyPressed(unsigned short key);
};

