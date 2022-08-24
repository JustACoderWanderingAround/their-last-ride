#pragma once
#include "Scene.h"
#include "Object.h"
#include <vector>

enum OSObject {
    OBJECT_OVERVIEW_BACKGROUND,
    OBJECT_OVERVIEW_BLANK_REAPER_NOTE,
    OBJECT_OVERVIEW_REAPER_NOTE,
    OBJECT_RIDE_NUMBER,
    OBJECT_OVERVIEW_BLANK_NORMAL_NOTE,
    OBJECT_OVERVIEW_NORMAL_NOTE,
    OBJECT_OVERVIEW_BLACK_SCREEN,
    NUM_OBJECT_OVERVIEW
};

class OverviewScene :
    public Scene
{
private:
    std::array<Object*, NUM_OBJECT_OVERVIEW> _objList;
    std::vector<Object*> _renderQueue;
    std::vector<Object*> _fadeQueue;
    std::vector<Object*> _unfadeQueue;
    int rideNumber;
public:
    int sceneClicks;
    OverviewScene();
    void Init();
    void Update(double dt);
    void UpdateText(Ride* r);
    void Render();
    void Exit();
    void HandleInput();
};

