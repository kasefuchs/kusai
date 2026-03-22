#include "kusai/markov/AbstractMarkov.hpp"

#include <cstdint>
#include <mutex>
#include <vector>

#include "kusai/graph/Node.hpp"

namespace kusai {
void AbstractMarkov::train(const std::vector<std::vector<NodeId>>& sequences) {
  std::unique_lock lock(mutex_);
  return trainUnlocked(sequences);
}

std::optional<NodeId> AbstractMarkov::nextNode(const std::vector<NodeId>& context) const {
  std::shared_lock lock(mutex_);
  return nextNodeUnlocked(context);
}

std::vector<NodeId> AbstractMarkov::generateSequence(const std::vector<NodeId>& context, uint32_t limit) const {
  std::shared_lock lock(mutex_);
  std::vector<NodeId> result = context;

  while (limit--) {
    auto node = nextNode(result);
    if (!node.has_value()) break;

    result.push_back(*node);
  }

  return result;
}
}  // namespace kusai
