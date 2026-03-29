#include "kusai/markov/SimpleMarkov.hpp"

#include <mutex>
#include <optional>
#include <random>
#include <string>
#include <vector>

#include "kusai/graph/AbstractGraph.hpp"
#include "kusai/graph/Edge.hpp"
#include "kusai/graph/Node.hpp"

namespace kusai {
nlohmann::json SimpleMarkov::serialize() const {
  std::shared_lock lock(mutex_);
  return {{"graph", graph->serialize()}};
}

bool SimpleMarkov::deserialize(const nlohmann::json& data) {
  std::unique_lock lock(mutex_);
  return graph->deserialize(data.at("graph"));
}

void SimpleMarkov::trainUnlocked(const std::vector<std::vector<NodeId> >& sequences) {
  for (auto& seq : sequences) {
    NodeId prev = 0;
    for (const auto node : seq) {
      graph->ensureNode(node);
      if (prev) {
        graph->modifyEdge(graph->ensureEdge(prev, node), [](Edge& edge) { edge.weight++; });
      }

      prev = node;
    }
  }
}

std::optional<NodeId> SimpleMarkov::nextNodeUnlocked(const NodeId current) const {
  const auto outgoing = graph->getOutgoingEdges(current);
  if (outgoing.empty()) return std::nullopt;

  std::vector<std::uint32_t> weights;
  weights.reserve(outgoing.size());
  for (const auto& edge : outgoing) {
    weights.push_back(edge.weight);
  }

  std::discrete_distribution dist(weights.begin(), weights.end());
  const auto& chosen = outgoing[dist(rng_)];

  return chosen.target;
}

std::optional<NodeId> SimpleMarkov::nextNodeUnlocked(const std::vector<NodeId>& context) const {
  const auto current = context.back();

  return nextNodeUnlocked(current);
}
}  // namespace kusai
