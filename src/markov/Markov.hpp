#pragma once

#include <random>

#include "AbstractMarkov.hpp"
#include "Graph.hpp"

class Markov : public AbstractMarkov {
public:
  explicit Markov(Graph &graph) : AbstractMarkov(graph) {}

  void train(const std::vector<std::vector<graph::Node *>> &sequences) override;

  graph::Node *nextNode(const graph::Node &current) const;

  graph::Node *nextNode(const std::vector<graph::Node *> &context) const override;

  std::vector<graph::Node *> generateNodes(const std::vector<graph::Node *> &context, uint32_t limit) const override;

  void serialize(google::protobuf::Any &out) const override;

  void deserialize(const google::protobuf::Any &in) override;

private:
  mutable std::mt19937 rng_{std::random_device{}()};
};
