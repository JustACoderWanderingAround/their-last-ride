#pragma once
#include "Scene.h"
class TrainScene : public Scene
{
private:
public:
	TrainScene() {}
	void Init();
	void Exit();
	void Update(double dt);
	void Render();
};

