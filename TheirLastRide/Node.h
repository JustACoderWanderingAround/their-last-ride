#pragma once
#include <string>
#include <vector>
struct Node
{
	//data
	unsigned int id;
	std::string text;
	std::vector<unsigned int> results;
	std::vector<unsigned int> options;
	Node* next;
	
};

