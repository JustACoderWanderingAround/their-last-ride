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
	_Ticket (*ticket),
	_RailPass (*railpass),
	_currentNode(nullptr)
{

}


InteractablePerson::InteractablePerson(const std::string& name)
	: _name(name), _currentNode(nullptr)
{
	std::string filepath = "Sprites\\Passengers\\" + _name + ".png";
	_txt.loadImage(filepath);
	_txt.setBlendMode(SDL_BLENDMODE_BLEND);
	loadNodes();

}

void InteractablePerson::interact()
{
	//TrainScene* mainScene = static_cast<TrainScene*>(scene);
	//mainScene->getButtons()->clear();
	//if (option != NULL) {
	//	_currentNode = _nodes[_currentNode->results[option]];
	//}
	//const int y_offset = -50;
	//// Before or after a conversation, _currentNode should be nullptr.
	//if (_nodes.size() == 0) {
	//	std::cout << "No nodes to interact" << std::endl;
	//	return;
	//}
	//if (_currentNode == nullptr)
	//	_currentNode = _nodes.front();
	//if (_currentNode == _nodes.front()) {
	//	//write player text
	//	mainScene->WriteText({ _currentNode->playerText, TextManager::GetInstance()->getFonts()[FONT_REDENSEK] }, { 480, 500 });
	//	_currentNode = _nodes[_currentNode->results.front()];
	//}
	//else {
	//	//write npc 
	//	mainScene->WriteText({ _currentNode->npcText, TextManager::GetInstance()->getFonts()[FONT_REDENSEK] }, { 480, 500 });
	//	for (int i = 0; i < _currentNode->results.size(); i++)
	//	{
	//		mainScene->getButtons()->push_back(new Button());
	//		mainScene->getButtons()->back()->setCoords({ mainScene->getButtons()->back()->getCoords().x, y_offset * i });
	//	}
	//	//render options
	//	//_currentNode = _nodes[_currentNode->results[option]];
	//}
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

Node*& InteractablePerson::getCurrentNode()
{
	return _currentNode;
}
