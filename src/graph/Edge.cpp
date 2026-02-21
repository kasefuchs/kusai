#include "kusai/graph/Edge.hpp"

#include <absl/numeric/int128.h>

#include <string>
#include <utility>

#include "kusai/graph/Node.hpp"

void Edge::serialize(pugi::xml_node& self) const {
  self.append_attribute("source") = source;
  self.append_attribute("target") = target;
  self.append_attribute("weight") = weight;
}

void Edge::deserialize(const pugi::xml_node& self) {
  source = self.attribute("source").as_ullong();
  target = self.attribute("target").as_ullong();
  weight = self.attribute("weight").as_double();
}

std::string Edge::tagName() const { return "Edge"; }

EdgeId Edge::makeId(const NodeId source, const NodeId target) { return absl::MakeUint128(source, target); }

std::pair<NodeId, NodeId> Edge::splitId(const EdgeId id) {
  return {
      absl::Uint128High64(id),  // source
      absl::Uint128Low64(id)    // target
  };
}
