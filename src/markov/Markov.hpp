#pragma once

#include <random>

#include "Graph.hpp"

class Markov : public Graph {
public:
  Markov() = default;

  ~Markov() override = default;

  virtual void train(const std::vector<std::vector<graph::Node *>> &sequences);

  graph::Node *nextNode(const graph::Node &current) const;

  virtual graph::Node *nextNode(const std::vector<graph::Node *> &context) const;

  std::vector<graph::Node *> generateNodes(const std::vector<graph::Node *> &context, uint32_t limit) const;

private:
  mutable std::mt19937 rng_{std::random_device{}()};

protected:
  using Graph::edges_;
  using Graph::nodes_;
};
