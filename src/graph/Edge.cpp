#include "kusai/graph/Edge.hpp"

#include <xxhash.h>

#include <iostream>
#include <string>
#include <utility>

#include "kusai/graph/Node.hpp"

namespace kusai {
nlohmann::json Edge::serialize() const { return {{"source", source}, {"target", target}, {"weight", weight}}; }

void Edge::deserialize(const nlohmann::json& data) {
  data.at("source").get_to(source);
  data.at("target").get_to(target);
  data.at("weight").get_to(weight);
}

EdgeId Edge::makeId(const NodeId source, const NodeId target) {
  const NodeId pair[2] = {source, target};
  return XXH64(pair, sizeof(pair), 0);
}
}  // namespace kusai
