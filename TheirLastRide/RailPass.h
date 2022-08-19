#pragma once
#include <string>

class RailPass
{
public:
	RailPass();
	RailPass(std::string n, bool pt, int e);
	~RailPass();
	std::string getName();
	bool getPassType();
	int getExpiry();

protected:
	std::string _Name;
	bool _PassType;
	int _Expiry;
};

