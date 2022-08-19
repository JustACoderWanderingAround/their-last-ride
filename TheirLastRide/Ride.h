#pragma once
#include <string>
#include <vector>
class Ride
{
	int _interactableNumber;
	int _nonInteractableNumber;
	int _carriageNum;
public:
	std::string start;
	std::vector<std::string> stops;
	Ride();
	Ride(std::string str, std::vector<std::string> stp, int iN, int nN);
	Ride(std::string str, std::vector<std::string> stp, int iN, int nN, int cN);
	~Ride();
	int getInteractable();
	int getNonInteractable();
	bool loadAttributes();

};

