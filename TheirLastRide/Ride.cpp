#include "Ride.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;


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

//bool Ride::loadAttributes(int rideNumber)
//{
//	//TODO: make this into a loadJson function
//	
//}
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

bool Ride::checkInteractable(const std::string& name)
{
	return (std::find(_interactablePeople.begin(), _interactablePeople.end(), name) != _interactablePeople.end());
}

int Ride::getDate() const
{
	return _date;
}

int Ride::getWrongVerdict()
{
	return _wrongVerdictCount;
}
