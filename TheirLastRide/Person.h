#pragma once
#include <vector>
#include "Node.h"
#include "Object.h"

class Object;
class Person : public Object
{
protected:
	bool _isInteracting;
	std::vector<Node*> _nodes;
	int _PersonName;
public:
	std::vector<Node*> getNodes();
	int getPersonName();


};



