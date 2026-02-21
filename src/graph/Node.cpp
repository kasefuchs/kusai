#include "kusai/graph/Node.hpp"

#include <string>

void Node::serialize(pugi::xml_node& self) const { self.append_attribute("id") = id; }

void Node::deserialize(const pugi::xml_node& self) { id = self.attribute("id").as_ullong(); }

std::string Node::tagName() const { return "Node"; }
