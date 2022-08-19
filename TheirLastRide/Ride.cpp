#include "Ride.h"
#include <iostream>ad
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

Ride::Ride()

{
}

Ride::Ride(std::string str, std::vector<std::string> stp, int iN, int nN)
{
    start = str;
    stops = stp;
    _interactableNumber = iN;
    _nonInteractableNumber = nN;
}

Ride::~Ride()
{
}



int Ride::getInteractable()
{
    return _interactableNumber;
}

int Ride::getNonInteractable()
{
    return _nonInteractableNumber;
}

bool Ride::loadAttributes()
{
	//TODO: make this into a loadJson function
	std::ifstream f("Data\\Rides.json");
	json j;
	if (!f) {
		std::cout << "File not loaded succesfully.\n";
		return false;
	}
	else {
		j = json::parse(f);
	}
	
	//std::cout << _nodes[0];
	return true;
	/*for (int i = 0; i < tempNodes2.size(); i++)
	{
		std::cout << _nodes[i]->playerText << std::endl;
	}*/
}
