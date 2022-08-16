#pragma once
#include "Scene.h"
#include "TrainCabin.h"
#include <vector>
#include <string>
class TrainScene : public Scene
{
private:
	std::vector<TrainCabin> _cabins;
public:
	TrainScene(SDL_Window* w, SDL_Surface* s);
	void Init();
	void Exit();
	void Update(double dt);
	void Render();
	SDL_Surface* loadImage(std::string path);
};

