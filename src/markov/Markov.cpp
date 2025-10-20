// Copyright (c) Kasefuchs
// SPDX-License-Identifier: MIT

#include "Markov.hpp"

#include <random>

#include "markov.hpp"
#include "markov.pb.h"

graph::Node *Markov::getNodeByValue(const uint32_t value) const {
  markov::NodeMetadata meta;
  for (const auto &[_, node]: nodes_) {
    if (markov::unpackNodeMetadata(node.get(), &meta) && meta.value() == value) {
      return node.get();
    }
  }

  return nullptr;
}

graph::Node *Markov::nextNode(const graph::Node *current) const {
  std::vector<uint32_t> weights;
  std::vector<graph::Edge *> edges;
  for (const auto &edge: getOutgoingEdges(current)) {
    markov::EdgeMetadata meta;
    if (markov::unpackEdgeMetadata(edge, &meta)) {
      if (const uint32_t count = meta.count(); count != 0) {
        weights.push_back(count);
        edges.push_back(edge);
      }
    }
  }

  if (edges.empty()) return nullptr;

  std::discrete_distribution distribution(weights.begin(), weights.end());

  static std::mt19937 gen(std::random_device{}());

  return getNode(edges[distribution(gen)]->target());
}

void Markov::train(const std::vector<std::vector<uint32_t> > &sequences) {
  for (auto &edge: edges_) markov::resetEdgeMetadata(edge.get());

  std::unordered_map<uint32_t, graph::Node *> nodeIndex;
  for (const auto &sequence: sequences) {
    const graph::Node *prev = nullptr;
    for (uint32_t value: sequence) {
      const auto [it, inserted] = nodeIndex.try_emplace(value, nullptr);
      if (inserted && !((it->second = getNodeByValue(value)))) {
        it->second = addNode();
        markov::NodeMetadata meta;
        meta.set_value(value);
        markov::packNodeMetadata(it->second, &meta);
      }

      if (prev) {
        auto *edge = getOrAddEdge(prev, it->second);

        markov::EdgeMetadata meta;
        markov::unpackEdgeMetadata(edge, &meta);
        meta.set_count(meta.count() + 1);
        markov::packEdgeMetadata(edge, &meta);
      }

      prev = it->second;
    }
  }
}
