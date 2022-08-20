#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "Application.h"
#include "Ride.h"
/// <summary>
/// Scenes are to be derived classes of this abstract class.
/// </summary>
class Player;
class Scene
{
Player* mainPlayer;
Ride* mainRide;
public:
	Scene();
	Scene(int rideNum);
	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

