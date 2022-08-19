#include "Ride.h"
#include <iostream>ad
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

void to_json(json& j, const Ride& n) {
	j = json{ {"start", n.start}, {"stops", n.stops }};
}

void from_json(const json& j,Ride& n) {
	j.at("start").get_to(n.start);
	j.at("stops").get_to(n.stops);
}

Ride::Ride()

{
	loadAttributes();
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
	std::ifstream f("Data\\Ride.json");
	json j;
	if (!f) {
		std::cout << "File not loaded succesfully.\n";
		return false;
	}
	else {
		j = json::parse(f);
	}
	//std::vector<Ride> testRide = j.get<std::vector<Ride>>();
	//std::cout << _nodes[0];
	return true;
	/*for (int i = 0; i < tempNodes2.size(); i++)
	{
		std::cout << _nodes[i]->playerText << std::endl;
	}*/
}
