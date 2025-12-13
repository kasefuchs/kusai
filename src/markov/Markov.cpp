#include "Markov.hpp"

#include <random>

graph::Node *Markov::nextNode(const graph::Node &current) const {
  const auto outgoing = getOutgoingEdges(current);
  if (outgoing.empty()) return nullptr;

  std::vector<uint32_t> weights;
  for (const auto *edge: outgoing) weights.push_back(edge->weight());

  std::discrete_distribution dist(weights.begin(), weights.end());
  const auto *chosen = outgoing[dist(rng_)];

  return getNode(chosen->target());
}

void Markov::train(const std::vector<std::vector<graph::Node *> > &sequences) {
  for (const auto &edge: edges_ | std::views::values) edge->set_weight(0);

  for (auto &seq: sequences) {
    const graph::Node *prev = nullptr;

    for (const auto *node: seq) {
      if (prev) {
        auto *edge = getOrAddEdge(*prev, *node);
        edge->set_weight(edge->weight() + 1);
      }

      prev = node;
    }
  }
}
