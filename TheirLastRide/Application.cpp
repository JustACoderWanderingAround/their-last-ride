#include "Application.h"
#include "TrainScene.h"
#include <WinUser.h>
#include <iostream>
#include <SDL_ttf.h>

constexpr int SCR_WIDTH = 1280;
constexpr int SCR_HEIGHT = 720;
bool isWritingText = false;
unsigned int iterator = 0;

void Application::Init()
{
    _mouse_coords = { 0, 0 };
    _targetFps = 60;
    // Initialize SDL. SDL_Init will return -1 if it fails.
    if (TTF_Init() < 0) {
        std::cout << "Error initializing TTF: " << TTF_GetError() << std::endl;
        system("pause");
        // End the program
        exit(0);
    }
    IMG_Init(IMG_INIT_PNG);
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
    int imgFlags = IMG_INIT_PNG;
    // Get the surface from the window
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cout << "SDL_image could not initialize! SDL_image Error:" << IMG_GetError() << std::endl;
        system("pause");
        exit(0);
    }
    else     
        _winSurface = SDL_GetWindowSurface(_window);
    SDL_SetSurfaceBlendMode(_winSurface, SDL_BLENDMODE_BLEND);
    // Make sure getting the surface succeeded
    if (!_winSurface) {
        std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
        system("pause");
        // End the program
        exit(0);
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL) {
        std::cout << "Error getting renderer: " << SDL_GetError() << std::endl;
        system("pause");
        // End the program
        exit(0);
    }
}

Application::Application()
    :   _winSurface(NULL), _window(NULL), _renderer(NULL), _targetFps(60)
{
}

void Application::Run()
{
    float time_between_frames = 1 / _targetFps;
    Scene* mainScene = new TrainScene();
    mainScene->Init();
    auto nodes = static_cast<TrainScene*>(mainScene)->getCabins().front()->getSeats()[0]->getNodes();
    Node* currentNode = nodes.front();
    //std::cout << nodes.size();
    _timer.startTimer();
    while (!IsKeyPressed(VK_ESCAPE)) {
        _acceptInput = !static_cast<TrainScene*>(mainScene)->writingText;
        while (SDL_PollEvent(&_event)) {
            switch (_event.type) {
            case SDL_MOUSEMOTION:
                SDL_GetGlobalMouseState(&_mouse_coords.x, &_mouse_coords.y);
                break;
            case SDL_KEYDOWN:
                switch (_event.key.keysym.sym) {
                case SDLK_DOWN:
                    if (_acceptInput) {
                        static_cast<TrainScene*>(mainScene)->WriteText({ currentNode->npcText, TextManager::GetInstance()->getFonts()[FONT_REDENSEK],  White }, { SCR_WIDTH / 2 - 300, SCR_HEIGHT / 2 });
                        for (int i = 0; i < currentNode->results.size(); i++)
                        {
                            std::cout << nodes[currentNode->results[i]]->playerText << std::endl;
                        }
                        if (currentNode->results.size() != 0) {
                            currentNode = nodes[currentNode->results[0]];
                        }
                    }
                    break;
                }
            }
        }
        mainScene->Update(_timer.getElapsedTime());
        mainScene->Render();

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

void Application::pause(long long time)
{
    _timer.waitUntil(time);
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

SDL_Renderer* Application::getRenderer() const
{
    return _renderer;
}

SDL_Point Application::getMouseCoords() const
{
    return _mouse_coords;
}
