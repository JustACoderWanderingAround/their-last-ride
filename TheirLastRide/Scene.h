#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "Application.h"
class Scene
{
protected:
public:
	Scene();

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

