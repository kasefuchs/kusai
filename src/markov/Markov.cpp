// Copyright (c) Kasefuchs
// SPDX-License-Identifier: MIT

#include "Markov.hpp"

#include <random>

#include "markov.hpp"
#include "markov.pb.h"

graph::Node *Markov::getNodeByValue(const uint32_t value) const {
  const auto it = nodeByValueIndex_.find(value);
  return it != nodeByValueIndex_.end() ? it->second : nullptr;
}

graph::Node *Markov::nextNode(const graph::Node &current) const {
  const auto outgoing = getOutgoingEdges(current);
  if (outgoing.empty()) return nullptr;

  std::vector<uint32_t> weights;
  std::vector<std::reference_wrapper<graph::Edge> > edges;
  weights.reserve(outgoing.size());
  edges.reserve(outgoing.size());

  for (auto &edge: outgoing) {
    markov::EdgeMetadata meta;
    if (markov::unpackEdgeMetadata(edge, &meta) && meta.count() != 0) {
      weights.push_back(meta.count());
      edges.push_back(edge);
    }
  }

  if (edges.empty()) return nullptr;

  std::discrete_distribution<> dist(weights.begin(), weights.end());
  const auto &selectedEdge = edges[dist(rng_)];
  return getNode(selectedEdge.get().target());
}

void Markov::train(const std::vector<std::vector<uint32_t> > &sequences) {
  for (auto &[_, edge]: edges_) markov::resetEdgeMetadata(*edge);

  for (const auto &sequence: sequences) {
    const graph::Node *prev = nullptr;
    for (uint32_t value: sequence) {
      graph::Node *node = getNodeByValue(value);
      if (!node) {
        node = &addNode();
        markov::NodeMetadata meta;
        meta.set_value(value);
        markov::packNodeMetadata(*node, meta);
        nodeByValueIndex_[value] = node;
      }

      if (prev) {
        auto &edge = getOrAddEdge(*prev, *node);
        markov::EdgeMetadata meta;
        markov::unpackEdgeMetadata(edge, &meta);
        meta.set_count(meta.count() + 1);
        markov::packEdgeMetadata(edge, meta);
      }

      prev = node;
    }
  }
}

void Markov::deserialize(const graph::Graph &in) {
  Graph::deserialize(in);

  nodeByValueIndex_.clear();
  for (const auto &[_, node]: nodes_) {
    markov::NodeMetadata meta;
    if (markov::unpackNodeMetadata(*node, &meta)) {
      nodeByValueIndex_[meta.value()] = node.get();
    }
  }
}
