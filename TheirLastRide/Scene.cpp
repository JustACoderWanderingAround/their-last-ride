#include "Scene.h"

Scene::Scene()

{
	mainRide = new Ride();
	mainRide->loadAttributes(0);
}
Scene::Scene(int rideNum)

{
	mainRide = new Ride();
	mainRide->loadAttributes(rideNum);
}