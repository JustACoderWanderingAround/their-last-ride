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

enum SceneName
{
	SCENE_TRAIN,
	SCENE_MAINMENU,
	SCENE_INTRO,
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
	Scene* _mainScene;
	
public:
	Application();
	void Init();
	void Run();
	void Exit();
	void changeScene(Scene* scene);
	SDL_Window* getWindow() const;
	SDL_Surface* getWindowSurface() const;
	SDL_Renderer* getRenderer() const;
	static bool IsKeyPressed(unsigned short key);
	SDL_Point getMouseCoords() const;
	SDL_Event* getEvent();
	std::vector<SDL_Event>& GetFrameEvents();
};

