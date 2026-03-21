#include "kusai/markov/SimpleMarkov.hpp"

#include <optional>
#include <random>
#include <string>
#include <vector>

#include "kusai/graph/AbstractGraph.hpp"
#include "kusai/graph/Edge.hpp"
#include "kusai/graph/Node.hpp"

namespace kusai {
void SimpleMarkov::train(const std::vector<std::vector<NodeId> >& sequences) {
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

std::optional<NodeId> SimpleMarkov::nextNode(const NodeId current) const {
  const auto outgoing = graph->getOutgoingEdges(current);
  if (outgoing.empty()) return std::nullopt;

  std::vector<double> weights;
  weights.reserve(outgoing.size());
  for (const auto& edge : outgoing) {
    weights.push_back(edge.weight);
  }

  std::discrete_distribution dist(weights.begin(), weights.end());
  const auto& chosen = outgoing[dist(rng_)];

  return chosen.target;
}

std::optional<NodeId> SimpleMarkov::nextNode(const std::vector<NodeId>& context) const {
  const auto current = context.back();

  return nextNode(current);
}

void SimpleMarkov::serialize(pugi::xml_node& self) const { graph->serializeToParent(self); }

void SimpleMarkov::deserialize(const pugi::xml_node& self) { graph->deserializeFromParent(self); }

std::string SimpleMarkov::tagName() const { return "SimpleMarkov"; }
}  // namespace kusai
