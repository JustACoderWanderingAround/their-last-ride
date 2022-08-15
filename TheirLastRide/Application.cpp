#include "Application.h"
#include "TrainScene.h"
#include <WinUser.h>

void Application::Init()
{
    _target_fps = 60;
}

void Application::Run()
{
    float time_between_frames = 1 / _target_fps;
    Scene* mainScene = new TrainScene();
    mainScene->Init();
    _timer.startTimer();
    while (!IsKeyPressed(VK_ESCAPE)) {
        mainScene->Update(_timer.getElapsedTime());
        mainScene->Render();
        _timer.waitUntil(time_between_frames);
    }
    mainScene->Exit();
    delete mainScene;
}

void Application::Exit()
{
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}
