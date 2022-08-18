#include "Node.h"


Node::Node()
	: results(std::vector<unsigned int>())
{
}

Node::Node(const std::string& t, const std::vector<unsigned int>& r)
	: playerText(t), results(r)
{
}

