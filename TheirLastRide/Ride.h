#pragma once
#include <string>
#include <vector>
class Ride
{
	int _interactableNumber;
	int _nonInteractableNumber;
	int _carriageNum;
	int _date;
public:
	std::string start;
	std::vector<std::string> stops;
	std::vector<std::string> invalidStops;
	Ride();
	Ride(std::string str, std::vector<std::string> stp, int iN, int nN);
	Ride(std::string str, std::vector<std::string> stp, int iN, int nN, int cN, int d);
	~Ride();
	int getInteractable();
	int getNonInteractable();
	int getCarriageNum();
	int getDate();
	bool loadAttributes(int rideNumber);
	void setDate(int d);
	void setInteractableNumber(int in);
	void setNonInterableNumber(int nin);
	void setCarriageNum(int cn);

};

