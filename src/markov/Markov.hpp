// Copyright (c) Kasefuchs
// SPDX-License-Identifier: MIT

#pragma once

#include "Graph.hpp"

class Markov : public Graph {
public:
  Markov() = default;

  ~Markov() = default;

  [[nodiscard]] graph::Node *getNodeByValue(uint32_t value) const;

  graph::Node *nextNode(const graph::Node *current) const;

  void train(const std::vector<std::vector<uint32_t>> &sequences);

protected:
  using Graph::edges_;
  using Graph::nodes_;
};
