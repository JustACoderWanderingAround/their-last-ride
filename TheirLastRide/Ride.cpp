#include "Ride.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

void to_json(json& j, const Ride& n) {
	j = json{ {"start", n.start}, {"stops", n.stops }, {"invalid", n.invalidStops}, {"people", n.interactablePeople}, {"carriageNum", n.carriageNum}, {"date", n.date}};
}

void from_json(const json& j,Ride& n) {
	j.at("start").get_to(n.start);
	j.at("stops").get_to(n.stops);
	j.at("invalid").get_to(n.invalidStops);
	j.at("people").get_to(n.interactablePeople);
	j.at("carriageNum").get_to(n.carriageNum);
	j.at("date").get_to(n.date);
}

Ride::Ride()
{
	interactableNumber = 1;
	nonInteractableNumber = 1;
}

Ride::Ride(std::string str, std::vector<std::string> stp, int iN, int nN)
{
    start = str;
    stops = stp;
    interactableNumber = iN;
    nonInteractableNumber = nN;
}
Ride::Ride(std::string str, std::vector<std::string> stp, int iN, int nN, int cN, int d)
{
	start = str;
	stops = stp;
	interactableNumber = iN;
	nonInteractableNumber = nN;
	carriageNum = cN;
	date = d;
}

Ride::~Ride()
{
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
	interactableNumber = testRide[rideNumber].interactableNumber;
	nonInteractableNumber = testRide[rideNumber].nonInteractableNumber;
	carriageNum = testRide[rideNumber].carriageNum;
	date = testRide[rideNumber].date;
	return true;
}
void Ride::setWrongVerdict(int wv)
{
	_wrongVerdictCount = wv;
}

bool Ride::operator==(const std::string& s) const
{
	return true;
}

int Ride::getDate()
{
	return date;
}

int Ride::getWrongVerdict()
{
	return _wrongVerdictCount;
}
