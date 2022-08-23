#include "RailPass.h"
#include "json.hpp"
//using json = nlohmann::json;
//
//
//void to_json(json& j, const RailPass& n) {
//	j = json{};
//}
//
//void from_json(const json& j, RailPass& n) {
//
//}


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

