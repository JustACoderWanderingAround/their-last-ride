#include "Ride.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

void to_json(json& j, const Ride& n) {
	j = json{ {"start", n.start}, {"stops", n.stops }, {"invalid", n.invalidStops}, {"people", n.interactablePeople}};
}

void from_json(const json& j,Ride& n) {
	j.at("start").get_to(n.start);
	j.at("stops").get_to(n.stops);
	j.at("invalid").get_to(n.invalidStops);
	j.at("people").get_to(n.interactablePeople);
}

Ride::Ride()
{
	_interactableNumber = 1;
	_nonInteractableNumber = 1;
}

Ride::Ride(std::string str, std::vector<std::string> stp, int iN, int nN)
{
    start = str;
    stops = stp;
    _interactableNumber = iN;
    _nonInteractableNumber = nN;
}
Ride::Ride(std::string str, std::vector<std::string> stp, int iN, int nN, int cN, int d)
{
	start = str;
	stops = stp;
	_interactableNumber = iN;
	_nonInteractableNumber = nN;
	_carriageNum = cN;
	_date = d;
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

int Ride::getCarriageNum()
{
	return _carriageNum;
}

bool Ride::loadAttributes(int rideNumber)
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
	std::vector<Ride> testRide = j.get<std::vector<Ride>>();
	start = testRide[rideNumber].start;
	stops = testRide[rideNumber].stops;
	invalidStops = testRide[rideNumber].invalidStops;
	interactablePeople = testRide[rideNumber].interactablePeople;
	//std::cout << _nodes[0];
	return true;
	/*for (int i = 0; i < tempNodes2.size(); i++)
	{
		std::cout << _nodes[i]->playerText << std::endl;
	}*/
}
void Ride::setDate(int d)
{
	_date = d;
}
void Ride::setInteractableNumber(int in)
{
	_interactableNumber = in;
}
void Ride::setNonInterableNumber(int nin)
{
	_nonInteractableNumber = nin;
}
void Ride::setCarriageNum(int cn)
{
	_carriageNum = cn;
}
void Ride::setWrongVerdict(int wv)
{
	_wrongVerdict = wv;
}
int Ride::getDate()
{
	return _date;
}

int Ride::getWrongVerdict()
{
	return _wrongVerdict;
}
