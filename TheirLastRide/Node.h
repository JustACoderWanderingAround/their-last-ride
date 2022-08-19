#pragma once
#include <string>
#include <vector>
#include "json.hpp"
using json = nlohmann::json;

/// <summary>
/// The structure for our data for dialogue.
/// </summary>
/// <param name="playerText">The text that the player will say to the NPC (usually will be shown as an option in a button)</param>
/// <param name="npcText">The text that the NPC will say to the player (could be a question or something)</param>
/// <param name="results">(Nodes are in sequence) The list of where the node could potentially branch towards based on the option chosen to implement flow and logic (Remember that the first node is 0.)</param>
struct Node
{
	//data
	std::string playerText;
	std::string npcText;
	std::vector<unsigned int> results;
	Node();
	Node(const std::string& t, const std::vector<unsigned int>& r);
};




