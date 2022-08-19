#pragma once
#include <vector>
#include "Node.h"
#include "Object.h"

class Object;
class Player;
class Person : public Object
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



