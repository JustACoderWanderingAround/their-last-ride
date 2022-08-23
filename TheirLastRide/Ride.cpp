#include "Ride.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

void to_json(json& j, const Ride& n) {
	j = json{ {"start", n.getStart() }, {"stops", n.getStops() }, {"invalid", n.getInvalidStops() }, {"people", n.getInteractablePeople() }, {"carriageNum", n.getCarriageNum() } , {"nonInteractableNum", n.getNonInteractive() } , {"date", n.getDate() } };
}

void from_json(const json& j,Ride& n) {
	n.setStart(j.at("start").get<std::string>());
	n.setStops(j.at("stops").get<std::vector<std::string>>());
	n.setInvalidStops(j.at("invalid").get<std::vector<std::string>>());
	n.setInteractablePeople(j.at("people").get<std::vector<std::string>>());
	n.setCarriageNum(j.at("carriageNum").get<int>());
	n.setNonInteractableNumber(j.at("nonInteractableNum").get<int>());
	n.setDate(j.at("date").get<int>());
	n.setInteractableNumber(n.getInteractablePeople().size());
}

Ride::Ride()
{
	_interactableNumber = 1;
	_nonInteractableNumber = 1;
}

Ride::Ride(std::string str, std::vector<std::string> stp, int iN, int nN)
{
    _start = str;
    _stops = stp;
    _interactableNumber = iN;
    _nonInteractableNumber = nN;
}
Ride::Ride(std::string str, std::vector<std::string> stp, int iN, int nN, int cN, int d)
{
	_start = str;
	_stops = stp;
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

int Ride::getNonInteractable() const
{
    return _nonInteractableNumber;
}

int Ride::getCarriageNum() const
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
	_start = testRide[rideNumber].getStart();
	_stops = testRide[rideNumber].getStops();
	_invalidStops = testRide[rideNumber].getInvalidStops();
	_interactablePeople = testRide[rideNumber].getInteractablePeople();
	//std::cout << _nodes[0];
	return true;
	/*for (int i = 0; i < tempNodes2.size(); i++)
	{
		std::cout << _nodes[i]->playerText << std::endl;
	}*/
}
void Ride::setStart(const std::string& s)
{
	_start = s;
}
void Ride::setStops(const std::vector<std::string>& s)
{
	_stops = s;
}
void Ride::setInvalidStops(const std::vector<std::string>& is)
{
	_invalidStops = is;
}
void Ride::setInteractablePeople(const std::vector<std::string>& ip)
{
	_interactablePeople = ip;
}
std::string Ride::getStart() const
{
	return _start;
}
std::vector<std::string> Ride::getStops() const
{
	return _stops;
}
std::vector<std::string> Ride::getInvalidStops() const
{
	return _invalidStops;
}
std::vector<std::string> Ride::getInteractablePeople() const
{
	return _interactablePeople;
}
void Ride::setDate(int d)
{
	_date = d;
}
void Ride::setInteractableNumber(int in)
{
	_interactableNumber = in;
}
void Ride::setNonInteractableNumber(int nin)
{
	_nonInteractableNumber = nin;
}
void Ride::setCarriageNum(int cn)
{
	_carriageNum = cn;
}
void Ride::setWrongVerdict(int wv)
{
	_wrongVerdictCount = wv;
}

bool Ride::operator==(const std::string& s) const
{
	return true;
}

int Ride::getDate() const
{
	return _date;
}

int Ride::getWrongVerdict()
{
	return _wrongVerdictCount;
}
