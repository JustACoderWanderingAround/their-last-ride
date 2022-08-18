#include "InteractablePerson.h"
#include "Player.h"
#include <iostream>
#include "json.hpp"
#include <fstream>
using json = nlohmann::json;

void to_json(json& j, const Node& n) {
	j = json{ {"msg", n.text}, {"results", n.results} };
}

void from_json(const json& j, Node& n) {
	j.at("msg").get_to(n.text);
	j.at("results").get_to(n.results);
}

InteractablePerson::InteractablePerson()
{

	std::ifstream f("Data//people.json");
	json j;
	if (!f) {
		std::cout << "File not loaded succesfully.";
	}
	else {
		j = json::parse(f);
	}
	std::vector<Node> tempNodes2 = j.get<std::vector<Node>>();
	//std::cout << _nodes[0];
	for (int i = 0; i < tempNodes2.size(); i++)
	{
		_nodes.push_back(new Node());
		*(_nodes.back()) = tempNodes2[i];
	}
	for (int i = 0; i < tempNodes2.size(); i++)
	{
		std::cout << _nodes[i]->text << std::endl;
	}
}


void InteractablePerson::interact(Player p)
{
	std::cout << "temp" << std::endl;
}

bool InteractablePerson::verdictChecker(bool _PlayerVerdict)
{
	
	return (_PlayerVerdict == _PredetermindedVerdict);
	
}
Ticket InteractablePerson::getTicket()
{
	return _Ticket;
}
RailPass InteractablePerson::getRailPass()
{
	return _RailPass;
}


std::string InteractablePerson::getName() 
{
	return _name;
}

bool InteractablePerson::getPassType()
{
	return _PassType;
}
