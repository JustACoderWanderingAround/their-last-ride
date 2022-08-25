#pragma once
#include "timer.h"
#include "Singleton.h"
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include "Text.h"
#include "InteractablePerson.h"
#include "Scene.h"
#include <vector>
#include "Ride.h"

enum RideName
{
	RIDE_1,
	RIDE_2,
	RIDE_3,
	NUM_RIDE
};

enum SceneName
{
	SCENE_TRAIN,
	SCENE_MAINMENU,
	SCENE_INTRO,
	SCENE_OVERVIEW,
	SCENE_END,
	NUM_SCENE
};

class Scene;
class Application : public Singleton<Application>
{
private:
	float _targetFps;
	Timer _timer;
	SDL_Surface* _winSurface;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Event _event;
	bool _acceptInput;
	SDL_Point _mouse_coords;
	std::array <Scene*, NUM_SCENE> _scenes;
	std::array<Ride*, NUM_RIDE> _rides;
	Scene* _mainScene;
	int _currentRide;
public:
	Application();
	void Init();
	void Run();
	void Exit();
	void loadRides();
	SDL_Window* getWindow() const;
	SDL_Surface* getWindowSurface() const;
	SDL_Renderer* getRenderer() const;
	static bool IsKeyPressed(unsigned short key);
	SDL_Point getMouseCoords() const;
	std::array<Scene*, NUM_SCENE> getScenes() const;
	SDL_Event* getEvent();
	std::array<Ride*, NUM_RIDE> getRides() const;
	void setCurrentRide(int iterator);
	int getCurrentRide() const;
	void updateCurrentRide();
	std::vector<SDL_Event>& GetFrameEvents();
	void changeScene(Scene* scene);
};

