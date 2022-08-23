#include "InteractablePerson.h"
#include "Player.h"
#include <iostream>
#include "json.hpp"
#include <fstream>
#include "ObjectBuilder.h"
#include "Application.h"
#include "TextManager.h";
using json = nlohmann::json;

void to_json(json& j, const Node& n) {
	j = json{ {"playerText", n.playerText}, {"npcText", n.npcText } ,{"results", n.results}};
}

void from_json(const json& j, Node& n) {
	j.at("playerText").get_to(n.playerText);
	j.at("npcText").get_to(n.npcText);
	j.at("results").get_to(n.results);
}

InteractablePerson::InteractablePerson()
{

}

bool InteractablePerson::loadNodes()	
{
	std::string fp = "Data\\" + _name + ".json"; //file path
	std::ifstream f(fp); // file
	json j; //json object
	if (!f) {
		std::cout << "File not loaded succesfully.\n";
		return false;
	}
	else {
		try
		{
			j = json::parse(f); //load the file contents into the json object
		}
		catch (json::parse_error& ex)
		{
			std::cout << "parse error " << ex.id << std::endl;
		}
	}
	std::vector<Node> tempNodes = j.get<std::vector<Node>>(); //convert the json object into vector of nodes
	for (int i = 0; i < tempNodes.size(); i++)
	{
		_nodes.push_back(new Node()); // assign a default empty node on the heap to a pointer in the vector
		*(_nodes.back()) = tempNodes[i]; // place the nodes with the file content data into those nodes
	}
	return true;
}

InteractablePerson::InteractablePerson(std::string name, bool passType, bool verdict, Ticket* ticket, RailPass* railpass)
	: _name (name),
	_PassType (passType),
	_PredetermindedVerdict (verdict),
	_Ticket (ticket),
	_RailPass (railpass),
	_currentNode(nullptr)
{

}


InteractablePerson::InteractablePerson(const std::string& name)
	: _name(name), _currentNode(nullptr), _RailPass(nullptr)
{
	std::string filepath = "Sprites\\Passengers\\" + _name + ".png";
	_txt.loadImage(filepath);
	_txt.setBlendMode(SDL_BLENDMODE_BLEND);
	_txt.setScale(1.1);
	loadNodes();
	_RailPass = new RailPass(name, true, 2);

}


bool InteractablePerson::verdictChecker(bool _PlayerVerdict)
{
	
	return (_PlayerVerdict == _PredetermindedVerdict);
	std::cout << "correct" << std::endl;
	
}
Ticket* InteractablePerson::getTicket()
{
	return _Ticket;
}
RailPass* InteractablePerson::getRailPass()
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

Node*& InteractablePerson::getCurrentNode()
{
	return _currentNode;
}

void InteractablePerson::setTicket(Ticket* t)
{
	_Ticket = t;
}

void InteractablePerson::setRailPass(RailPass* r)
{
	_RailPass = r;
}
