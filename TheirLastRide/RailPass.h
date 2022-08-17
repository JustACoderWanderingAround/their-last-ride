#pragma once
class RailPass
{
public:
	int getName();
	int getPassType();
	int getExpiry();

protected:
	int _Name;
	int _PassType;
	int _Expiry;
};

