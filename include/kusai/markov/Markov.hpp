#pragma once

#include <random>

#include "AbstractMarkov.hpp"

class Markov : public AbstractMarkov {
 public:
  explicit Markov(AbstractGraph& graph) : AbstractMarkov(graph) {}

  void train(const std::vector<std::vector<NodeId>>& sequences) override;

  [[nodiscard]] std::optional<NodeId> nextNode(NodeId current) const;

  [[nodiscard]] std::optional<NodeId> nextNode(const std::vector<NodeId>& context) const override;

  void serialize(google::protobuf::Any& out) const override;

  void deserialize(const google::protobuf::Any& in) override;

 private:
  mutable std::mt19937 rng_{std::random_device{}()};
};
