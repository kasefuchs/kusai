#include "kusai/graph/Edge.hpp"

#include <xxhash.h>

#include <iostream>
#include <string>
#include <utility>

#include "kusai/graph/Node.hpp"

namespace kusai {
void Edge::serialize(pugi::xml_node& self) const {
  self.append_attribute("source") = source;
  self.append_attribute("target") = target;
  self.append_attribute("weight") = weight;
}

void Edge::deserialize(const pugi::xml_node& self) {
  source = self.attribute("source").as_ullong();
  target = self.attribute("target").as_ullong();
  weight = self.attribute("weight").as_uint();
}

std::string Edge::tagName() const { return "Edge"; }

EdgeId Edge::makeId(const NodeId source, const NodeId target) {
  const NodeId pair[2] = {source, target};
  return XXH64(pair, sizeof(pair), 0);
}
}  // namespace kusai
