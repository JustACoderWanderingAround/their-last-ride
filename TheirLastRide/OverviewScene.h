#pragma once
#include "Scene.h"
#include "Object.h"
#include <vector>

enum OSObject {
    OBJECT_OVERVIEW_BACKGROUND,
    OBJECT_OVERVIEW_BLANK_REAPER_NOTE,
    OBJECT_OVERVIEW_REAPER_NOTE,
    OBJECT_REPORTED_ALIVE,
    OBJECT_REPORTED_DEAD,
    OBJECT_EXPECTED_ALIVE,
    OBJECT_EXPECTED_DEAD,
    OBJECT_DISPARITY_ALIVE,
    OBJECT_DISPARITY_DEAD,
    OBJECT_RIDE_NUMBER,
    OBJECT_OVERVIEW_BLANK_NORMAL_NOTE,
    OBJECT_OVERVIEW_NORMAL_NOTE,
    OBJECT_EXPECTED_PASS,
    OBJECT_REPORTED_PASS,
    OBJECT_DISPARITY,
    OBJECT_LOST_REV,
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
    int expectedAlive;
    int expectedDead;
    int actualAlive;
    int actualDead;
public:
    int sceneClicks;
    void setExpected(int expA, int expD);
    void setActual(int actA, int actD);
    OverviewScene();
    void Init();
    void Update(double dt);
    void UpdateText(Ride* r);
    void Render();
    void Exit();
    void HandleInput();
};

