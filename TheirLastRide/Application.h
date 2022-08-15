#pragma once
#include "Scene.h"
#include "timer.h"

class Application
{
private:
	float _target_fps;
	Timer _timer;
public:
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
};

