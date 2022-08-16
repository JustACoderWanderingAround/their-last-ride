#include "Application.h"
#include "TrainScene.h"
#include <WinUser.h>
#include <iostream>

constexpr int SCR_WIDTH = 1280;
constexpr int SCR_HEIGHT = 720;

void Application::Init()
{
    _target_fps = 60;
    // Initialize SDL. SDL_Init will return -1 if it fails.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        system("pause");
        // End the program
        exit(0);
    }
    _window = SDL_CreateWindow("Their Last Ride", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_SHOWN);

    if (!_window) {
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        system("pause");
        // End the program
        exit(0);
    }

    // Get the surface from the window
    _winSurface = SDL_GetWindowSurface(_window);

    // Make sure getting the surface succeeded
    if (!_winSurface) {
        std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
        system("pause");
        // End the program
        exit(0);
    }
}

Application::Application()
    :   _winSurface(NULL), _window(NULL), _target_fps(60)
{
}

void Application::Run()
{
    float time_between_frames = 1 / _target_fps;
    Scene* mainScene = new TrainScene(_window, _winSurface);
    mainScene->Init();
    _timer.startTimer();
    while (!IsKeyPressed(VK_ESCAPE)) {
        mainScene->Update(_timer.getElapsedTime());
        mainScene->Render();
        SDL_UpdateWindowSurface(_window);
        _timer.waitUntil(time_between_frames);
    }
    mainScene->Exit();
    delete mainScene;
}

void Application::Exit()
{
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

SDL_Window* Application::getWindow() const
{
    return _window;
}


SDL_Surface* Application::getWindowSurface() const
{
    return _winSurface;
}
