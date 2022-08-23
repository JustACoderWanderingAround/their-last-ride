#pragma once
#include <string>
#include <vector>
class Ride
{
	
public:
	int interactableNumber;
	int nonInteractableNumber;
	int carriageNum;
	int date;
	int _wrongVerdictCount;
	std::string start;
	std::vector<std::string> stops;
	std::vector<std::string> invalidStops;
	std::vector<std::string> interactablePeople;
	Ride();
	Ride(std::string str, std::vector<std::string> stp, int iN, int nN);
	Ride(std::string str, std::vector<std::string> stp, int iN, int nN, int cN, int d);
	~Ride();
	int getDate();
	int getWrongVerdict();
	bool loadAttributes(int rideNumber);
	void setWrongVerdict(int wv);
	bool operator==(const std::string& s) const;
};

