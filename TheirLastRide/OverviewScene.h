#pragma once
#include "Scene.h"
class OverviewScene :
    public Scene
{
    OverviewScene();
    void Init();
    void Update(double dt);
    void Render();
    void Exit();
};

