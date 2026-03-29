#pragma once

#include <random>

#include "AbstractMarkov.hpp"

namespace kusai {
class SimpleMarkov : public AbstractMarkov {
 public:
  explicit SimpleMarkov(const std::shared_ptr<AbstractGraph>& graph) : AbstractMarkov(graph) {}

  [[nodiscard]] nlohmann::json serialize() const override;
  bool deserialize(const nlohmann::json& data) override;

 protected:
  void trainUnlocked(const std::vector<std::vector<NodeId> >& sequences) override;

  [[nodiscard]] std::optional<NodeId> nextNodeUnlocked(NodeId current) const;

  [[nodiscard]] std::optional<NodeId> nextNodeUnlocked(const std::vector<NodeId>& context) const override;

 private:
  mutable std::mt19937 rng_{std::random_device{}()};
};
}  // namespace kusai
