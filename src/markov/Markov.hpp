// Copyright (c) Kasefuchs
// SPDX-License-Identifier: MIT

#pragma once

#include <random>

#include "Graph.hpp"

class Markov : public Graph {
public:
  Markov() = default;

  ~Markov() = default;

  [[nodiscard]] graph::Node *getNodeByValue(uint32_t value) const;

  graph::Node *nextNode(const graph::Node &current) const;

  void train(const std::vector<std::vector<uint32_t> > &sequences);

  void deserialize(const graph::Graph &in);

private:
  mutable std::mt19937 rng_{std::random_device{}()};
  std::unordered_map<uint32_t, graph::Node *> nodeByValueIndex_;

protected:
  using Graph::edges_;
  using Graph::nodes_;
};
