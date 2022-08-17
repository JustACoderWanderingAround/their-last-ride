#pragma once
#include "Texture.h"
#include "Object.h"
#include "Scene.h"
#include "TrainCabin.h"
#include <vector>
#include <string>
#include <array>
#include "TextManager.h"
#include "ObjectBuilder.h"

enum OBJECT {
	OBJECT_BACKGROUND1,
	OBJECT_PLAYER,
	OBJECT_TEXT,
	NUM_OBJECT
};

class TrainScene : public Scene
{
private:
	std::array<Object, NUM_OBJECT> _objList;
	std::vector<Object> _renderQueue; //maybe change to deque/priority queue?
	std::vector<TrainCabin> _cabins;
public:
	TrainScene();
	void Init();
	void Exit();
	void Update(double dt);
	void Render();
	void createBottomRowChairs();
};

