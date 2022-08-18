#pragma once
#include <vector>
#include "Node.h"
class Player;
class Person
{
protected:
	bool _isInteracting;
	std::vector<Node*> _nodes;
	int _PersonName;
public:
	virtual void interact(Player p) = 0;
	std::vector<Node*> getNodes();
	int getPersonName();


};



