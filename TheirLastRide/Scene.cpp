#include "Scene.h"
#include "Player.h"
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

void Scene::setPlayer(Player* p)
{
	mainPlayer = p;
}

void Scene::setRide(Ride* r)
{
	mainRide = r;
}
