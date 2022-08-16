#pragma once
#include "Texture.h"
#include "Scene.h"
#include "TrainCabin.h"
#include <vector>
#include <string>
class TrainScene : public Scene
{
private:
	Texture _txt;
	std::vector<TrainCabin> _cabins;
public:
	TrainScene(SDL_Window* w, SDL_Surface* s, SDL_Renderer* r);
	void Init();
	void Exit();
	void Update(double dt);
	void Render();
	bool showImage(std::string path);
};

