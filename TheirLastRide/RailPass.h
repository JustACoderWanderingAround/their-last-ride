#pragma once
#include <string>

class RailPass
{
public:
	std::string getName();
	std::string getPassType();
	std::string getExpiry();
	void test();

protected:
	std::string _Name;
	std::string _PassType;
	std::string _Expiry;
};

