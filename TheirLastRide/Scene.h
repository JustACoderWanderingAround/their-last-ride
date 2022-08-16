#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "Application.h"
class Scene
{
protected:
	SDL_Window* m_Window;
	SDL_Surface* m_Surface;
public:
	Scene(SDL_Window* w, SDL_Surface* s);

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

