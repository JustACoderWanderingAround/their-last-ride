#pragma once
#include <string>
#include <vector>
#include "json.hpp"
using json = nlohmann::json;

struct Node
{
	//data
	std::string text;
	std::vector<unsigned int> results;
	Node* next;
	Node();
	Node(const std::string& t, const std::vector<unsigned int>& r);
	//void to_json(json& j, const Node& n);
	//void from_json(const json& j, Node& n);
};




