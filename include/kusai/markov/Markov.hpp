#pragma once

#include <random>

#include "AbstractMarkov.hpp"

class Markov : public AbstractMarkov {
 public:
  explicit Markov(AbstractGraph& graph) : AbstractMarkov(graph) {}

  void train(const std::vector<std::vector<NodeId> >& sequences) override;

  [[nodiscard]] std::optional<NodeId> nextNode(NodeId current) const;

  [[nodiscard]] std::optional<NodeId> nextNode(const std::vector<NodeId>& context) const override;

  void serialize(pugi::xml_node& self) const override;

  void deserialize(const pugi::xml_node& self) override;

  [[nodiscard]] std::string tagName() const override;

 private:
  mutable std::mt19937 rng_{std::random_device{}()};
};
