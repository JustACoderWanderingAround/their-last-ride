#pragma once
#include <string>
#include <vector>
class Ride
{
	std::string _start;
	std::vector<std::string> _stops;
	int _interactableNumber;
	int _nonInteractableNumber;
public:
	Ride();
	Ride(std::string str, std::vector<std::string> stp, int iN, int nN);
	~Ride();
	std::string getStart();
	std::vector<std::string> getStops();
	int getInteractable();
	int getNonInteractable();

};

