#pragma once
#include <string>

class RailPass
{
public:
	std::string getName();
	std::string getPassType();
	int getExpiry();

protected:
	std::string _Name;
	std::string _PassType;
	int _Expiry;
};

