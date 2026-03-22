#pragma once

#include <memory>
#include <vector>

#include "kusai/graph/AbstractGraph.hpp"

namespace kusai {
class AbstractMarkov : public Serializable {
 public:
  ~AbstractMarkov() override = default;

  std::shared_ptr<AbstractGraph> graph;

  void train(const std::vector<std::vector<NodeId>>& sequences);
  [[nodiscard]] std::optional<NodeId> nextNode(const std::vector<NodeId>& context) const;
  [[nodiscard]] std::vector<NodeId> generateSequence(const std::vector<NodeId>& context,
                                                     uint32_t limit = INT8_MAX) const;

 protected:
  mutable std::shared_mutex mutex_;

  explicit AbstractMarkov(const std::shared_ptr<AbstractGraph>& graph) : graph(graph) {}

  virtual void trainUnlocked(const std::vector<std::vector<NodeId>>& sequences) = 0;

  [[nodiscard]] virtual std::optional<NodeId> nextNodeUnlocked(const std::vector<NodeId>& context) const = 0;
};
}  // namespace kusai
