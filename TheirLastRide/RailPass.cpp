#include "RailPass.h"
#include "json.hpp"
using json = nlohmann::json;


//void to_json(json& j, const RailPass& n) {
//	j = json{ {"playerText", n.playerText}, {"npcText", n.npcText } ,{"results", n.results} };
//}
//
//void from_json(const json& j, RailPass& n) {
//	j.at("playerText").get_to(n.playerText);
//	j.at("npcText").get_to(n.npcText);
//	j.at("results").get_to(n.results);
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

