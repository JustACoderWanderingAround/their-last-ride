#pragma once
#include <string>

class RailPass
{
public:
	std::string getName();
	bool getPassType();
	int getExpiry();

protected:
	std::string _Name;
	bool _PassType;
	int _Expiry;
};

