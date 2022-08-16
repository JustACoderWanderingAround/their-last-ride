#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "Application.h"
class Scene
{
protected:
	SDL_Window* m_Window;
	SDL_Surface* m_Surface;
	SDL_Renderer* m_Renderer;
public:
	Scene(SDL_Window* w, SDL_Surface* s, SDL_Renderer* r);

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

