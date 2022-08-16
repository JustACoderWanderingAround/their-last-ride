#pragma once
#include "Scene.h"
#include "TrainCabin.h"
class TrainScene : public Scene
{
private:
public:
	TrainScene(SDL_Window* w, SDL_Surface* s);
	void Init();
	void Exit();
	void Update(double dt);
	void Render();
};

