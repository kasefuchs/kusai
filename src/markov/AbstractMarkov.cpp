#include "kusai/markov/AbstractMarkov.hpp"

#include <cstdint>
#include <vector>

#include "kusai/graph/Node.hpp"

std::vector<NodeId> AbstractMarkov::generateNodes(const std::vector<NodeId>& context, uint32_t limit) const {
  std::vector<NodeId> result = context;

  while (limit--) {
    auto node = nextNode(result);
    if (!node.has_value()) break;

    result.push_back(*node);
  }

  return result;
}
