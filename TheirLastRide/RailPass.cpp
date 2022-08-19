#include "RailPass.h"

RailPass::RailPass()
{
}

RailPass::RailPass(std::string n, bool pt, int e)
{
	_Name = n;
	_PassType = pt;
	_Expiry = e;
}

RailPass::~RailPass()
{
}

std::string RailPass::getName()
{
	return _Name;
}

bool RailPass::getPassType()
{
	return _PassType;
}

int RailPass::getExpiry()
{
	return _Expiry;
}

