#pragma once
#include <string>
#include <vector>
class Ride
{
	int _interactableNumber;
	int _nonInteractableNumber;
	int _carriageNum;
	int _date;
	int _wrongVerdictCount;
public:
	std::string start;
	std::vector<std::string> stops;
	std::vector<std::string> invalidStops;
	std::vector<std::string> interactablePeople;
	Ride();
	Ride(std::string str, std::vector<std::string> stp, int iN, int nN);
	Ride(std::string str, std::vector<std::string> stp, int iN, int nN, int cN, int d);
	~Ride();
	int getInteractable();
	int getNonInteractable();
	int getCarriageNum();
	int getDate();
	int getWrongVerdict();
	bool loadAttributes(int rideNumber);
	void setDate(int d);
	void setInteractableNumber(int in);
	void setNonInterableNumber(int nin);
	void setCarriageNum(int cn);
	void setWrongVerdict(int wv);
	bool operator==(const std::string& s) const;
};

