#pragma once
#include <vector>
#include "Node.h"
class Player;
class Person
{
protected:
	std::vector<Node*> _nodes;
	virtual void interact(Player p) = 0;
};

