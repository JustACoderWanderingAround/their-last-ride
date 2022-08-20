#pragma once
#include "timer.h"
#include "Singleton.h"
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include "Text.h"
#include "InteractablePerson.h"
#include "Scene.h"
#include <vector>

class Scene;
class Application : public Singleton<Application>
{
private:
	float _targetFps;
	Timer _timer;
	SDL_Surface* _winSurface;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Event _event;
	bool _acceptInput;
	SDL_Point _mouse_coords;
public:
	Application();
	void Init();
	void Run();
	void Exit();
	SDL_Window* getWindow() const;
	SDL_Surface* getWindowSurface() const;
	SDL_Renderer* getRenderer() const;
	static bool IsKeyPressed(unsigned short key);
	SDL_Point getMouseCoords() const;
	SDL_Event* getEvent();
	std::vector<SDL_Event>& GetFrameEvents();
};

