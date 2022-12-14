#include "Application.h"
#include "TrainScene.h"
#include "MenuScene.h"
#include "IntroScene.h"
#include "EndScene.h"
#include "OverviewScene.h"
#include <WinUser.h>
#include <iostream>
#include <SDL_ttf.h>
#include "Ride.h"
#include "Player.h"
#include <fstream>

bool gameRunning = false;

void to_json(json& j, const Ride& n) {
    j = json{ {"start", n.getStart() }, {"stops", n.getStops() }, {"invalid", n.getInvalidStops() }, {"people", n.getInteractablePeople() }, {"carriageNum", n.getCarriageNum() } , {"nonInteractableNum", n.getNonInteractable() } , {"date", n.getDate() }};
}

void from_json(const json& j, Ride& n) {
    n.setStart(j.at("start").get<std::string>());
    n.setStops(j.at("stops").get<std::vector<std::string>>());
    n.setInvalidStops(j.at("invalid").get<std::vector<std::string>>());
    n.setInteractablePeople(j.at("people").get<std::vector<std::string>>());
    n.setCarriageNum(j.at("carriageNum").get<int>());
    n.setNonInteractableNumber(j.at("nonInteractableNum").get<int>());
    n.setDate(j.at("date").get<int>());
    n.setInteractableNumber(n.getInteractablePeople().size());
}
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
    for (int i = 0; i < NUM_RIDE; i++)
    {
        _rides[i] = new Ride();
    }
    loadRides();
}

/// <summary>
/// Constructor to initialise values. Initalise the pointers as NULL, and set the target FPS in here.
/// </summary>
Application::Application()
    :   _winSurface(NULL), _window(NULL), _renderer(NULL), _targetFps(60), _currentRide(0)
{
    _scenes[SCENE_TRAIN] = new TrainScene();
    _scenes[SCENE_MAINMENU] = new MenuScene();
    _scenes[SCENE_INTRO] = new IntroScene();
    _scenes[SCENE_OVERVIEW] = new OverviewScene();
    _scenes[SCENE_END] = new EndScene();
}

/// <summary>
/// Run the application. Should be called after initialisation.
/// </summary>
void Application::Run()
{
    gameRunning = true;
    float time_between_frames = 1 / _targetFps;
    Player* player1 = new Player(_rides[RIDE_1]->getStops());
    //_rides[RIDE_1]->setNumDead(3);
    //ides[RIDE_1]->setNumAlive(1);
    auto trainScene = static_cast<TrainScene*>(_scenes[SCENE_TRAIN]);
    _mainScene = _scenes[SCENE_MAINMENU];//CHANGE TRAIN TO MAINMENU
    trainScene->setRide(_rides[_currentRide]);
    trainScene->setPlayer(player1);
    for (int i = 0; i < NUM_SCENE; i++)
    {
        // todo: remove before releasse
        //if (i == SCENE_TRAIN)
            //continue;
        _scenes[i]->Init();
    }
    _timer.startTimer();
    while (!IsKeyPressed(VK_ESCAPE) && gameRunning) {
        while (SDL_PollEvent(&_event) != 0)
        {
            GetFrameEvents().push_back(_event);
            if (_event.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(&_mouse_coords.x, &_mouse_coords.y);
            }

        }
        
        //_acceptInput = !static_cast<TrainScene*>(mainScene)->writingText;
        _mainScene->Update(_timer.getElapsedTime());
        _mainScene->Render();

        _timer.waitUntil(time_between_frames);
        GetFrameEvents().clear();
    }
    _mainScene->Exit();
    for (int i = 0; i < NUM_SCENE; i++)
    {
        if (_scenes[i] != nullptr) {
            delete _scenes[i];
        }
    }
}

/// <summary>
/// Exit the application, used for deleting the SDL processes before the destructor is called.
/// </summary>
void Application::Exit()
{
    for (auto ride : _rides) {
        if (ride != nullptr) {
            delete ride;
            ride = nullptr;
        }
    }
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Application::loadRides()
{
    std::ifstream f("Data\\Ride.json");
    json j;
    if (!f) {
        std::cout << "File not loaded succesfully.\n";
        exit(0);
    }
    else {
        j = json::parse(f);
    }
    std::vector<Ride> tempRides = j.get<std::vector<Ride>>();
    for (int i = 0; i < NUM_RIDE; i++)
    {
        *(_rides[i]) = tempRides[i];
    }
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

std::array<Scene*, NUM_SCENE> Application::getScenes() const
{
    return _scenes;
}

SDL_Event* Application::getEvent()
{
    return &_event;
}

std::array<Ride*, NUM_RIDE> Application::getRides() const
{
    return _rides;
}

void Application::setCurrentRide(int iterator)
{
    _currentRide = iterator;
}

int Application::getCurrentRide() const
{
    return _currentRide;
}

void Application::updateCurrentRide()
{
    static_cast<TrainScene*>(_scenes[SCENE_TRAIN])->setMainRide(_rides[_currentRide]);
}

/// <summary>
/// Get a list of events(SDL_Event) that happened during that frame
/// </summary>
/// <returns>Vector of SDL_Event</returns>
std::vector<SDL_Event>& Application::GetFrameEvents()
{
    static std::vector<SDL_Event> frame_events;
    return frame_events;
}

void Application::changeScene(Scene* scene)
{
    _mainScene->Exit();
    _mainScene = scene;
    GetFrameEvents().clear();
}

void Application::endGame()
{
    gameRunning = false;
}


