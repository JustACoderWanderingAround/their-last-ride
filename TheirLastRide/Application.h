#pragma once
#include "timer.h"
#include "Singleton.h"
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include "Text.h"
#include "InteractablePerson.h"
#include "Scene.h"

class Scene;
class Application : public Singleton<Application>
{
private:
	SDL_Point _mouse_coords;
	float _targetFps;
	Timer _timer;
	SDL_Surface* _winSurface;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Event _event;
	bool _acceptInput;
public:
	Application();
	void Init();
	void Run();
	void Exit();
	void pause(long long time);
	SDL_Window* getWindow() const;
	SDL_Surface* getWindowSurface() const;
	SDL_Renderer* getRenderer() const;
	SDL_Point getMouseCoords() const;
	static bool IsKeyPressed(unsigned short key);
};

