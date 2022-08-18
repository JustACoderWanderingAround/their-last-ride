#pragma once
#include <vector>
class Player;
class Person
{
protected:
	std::vector<Node*> _nodes;
	virtual void interact(Player p) = 0;
};

