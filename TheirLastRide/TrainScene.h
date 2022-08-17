#pragma once
#include "Texture.h"
#include "Object.h"
#include "Scene.h"
#include "TrainCabin.h"
#include <vector>
#include <string>
class TrainScene : public Scene
{
private:
	std::vector<Object> _objs; //maybe change to deque/priority queue?
	std::vector<TrainCabin> _cabins;
public:
	TrainScene();
	void Init();
	void Exit();
	void Update(double dt);
	void Render();
	bool createImage(std::string path, Texture& _txt);
};

