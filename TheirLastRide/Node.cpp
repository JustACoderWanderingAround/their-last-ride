#include "Node.h"


Node::Node()
	: results(std::vector<unsigned int>())
{
}

Node::Node(const std::string& t, const std::vector<unsigned int>& r)
	: text(t), results(r)
{
}

//void Node::to_json(json& j, const Node& n) {
//	j = json{ {"msg", n.text}, {"results", n.results } };
//}
//
//void Node::from_json(const json& j, Node& n) {
//	j.at("msg").get<std::string>();
//	j.at("results").get<std::vector<unsigned int>>();
//}
