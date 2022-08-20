#include "Application.h"
#include "TrainScene.h"
#include <WinUser.h>
#include <iostream>
#include <SDL_ttf.h>

/// <summary>
/// The window screen width.
/// </summary>
constexpr int SCR_WIDTH = 1280;
/// <summary>
/// The window screen height.
/// </summary>
constexpr int SCR_HEIGHT = 720;
/// <summary>
/// Will be true if the scene is rendering text currently, else false.
/// </summary>
bool isWritingText = false;

/// <summary>
/// Initialise the application.
/// </summary>
void Application::Init()
{
    _mouse_coords = { 0, 0 };
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

/// <summary>
/// Constructor to initialise values. Initalise the pointers as NULL, and set the target FPS in here.
/// </summary>
Application::Application()
    :   _winSurface(NULL), _window(NULL), _renderer(NULL), _targetFps(60)
{
}

/// <summary>
/// Run the application. Should be called after initialisation.
/// </summary>
void Application::Run()
{
    float time_between_frames = 1 / _targetFps;
    Scene* mainScene = new TrainScene();
    mainScene->Init();
    auto nodes = static_cast<TrainScene*>(mainScene)->getCabins().front()->getSeats()[0]->getNodes();
    Node* currentNode = nodes.front();
    std::cout << nodes.size();
    _timer.startTimer();
    while (!IsKeyPressed(VK_ESCAPE)) {
        _acceptInput = !static_cast<TrainScene*>(mainScene)->writingText;
        while (SDL_PollEvent(&_event)) {
            switch (_event.type) {
            case SDL_MOUSEBUTTONDOWN: {
                std::cout << "Mouse down\n" << _mouse_coords.x << "," << _mouse_coords.y << "\n";
                
                Person* obj = static_cast<TrainScene*>(mainScene)->getPersonClick();
                if (obj != nullptr)
                    obj->interact();
                break;
            }
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&_mouse_coords.x, &_mouse_coords.y);
                break;
            case SDL_KEYDOWN:
                switch (_event.key.keysym.sym) {
                case SDLK_DOWN:
                    if (_acceptInput) {
                        static_cast<TrainScene*>(mainScene)->WriteText({ currentNode->npcText, TextManager::GetInstance()->getFonts()[FONT_REDENSEK],  White }, { 480 , 500 });

                        for (int i = 0; i < currentNode->results.size(); i++)
                        {
                            std::cout << nodes[currentNode->results[i]]->playerText << std::endl;
                        }
                        if (currentNode->results.size() != 0) {
                            currentNode = nodes[currentNode->results[0]];
                        }
                    }
                    break;

                case SDLK_UP:
                    if (_acceptInput) {
                        static_cast<TrainScene*>(mainScene)->WriteText({ currentNode->playerText, TextManager::GetInstance()->getFonts()[FONT_REDENSEK],  White }, { 480 , 500 });

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

/// <summary>
/// Exit the application, used for deleting the SDL processes before the destructor is called.
/// </summary>
void Application::Exit()
{
    SDL_DestroyWindow(_window);
    SDL_Quit();
}


/// <summary>
/// Check if the user is holding down a key, check for this every frame.
/// </summary>
/// <param name="key">The key to check for.</param>
/// <returns>Return true if pressed, else false.</returns>
bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

/// <summary>
/// Get the SDL Window. SDL_Window is the window process for SDL. Used for rendering and back-end stuff.
/// </summary>
/// <returns>A pointer to the SDL Window.</returns>
SDL_Window* Application::getWindow() const
{
    return _window;
}

/// <summary>
/// Get the SDL window surface. SDL_Surface is the 'surface' on the window. It is different from a texture. Used for rendering.
/// </summary>
/// <returns>A pointer to the SDL surface.</returns>
SDL_Surface* Application::getWindowSurface() const
{
    return _winSurface;
}

/// <summary>
/// Get the SDL renderer. The renderer is used for displaying SDL_Textures on the surface of the window. Used for rendering functions.
/// </summary>
/// <returns>A pointer to the SDL renderer.</returns>
SDL_Renderer* Application::getRenderer() const
{
    return _renderer;
}

/// <summary>
/// Get the mouse coordinates. Usually updated after the mouse moves.
/// </summary>
/// <returns>An SDL_Point(Vector2 containing integers) of the mouse coordinates(x, y)</returns>
SDL_Point Application::getMouseCoords() const
{
    return _mouse_coords;
}
