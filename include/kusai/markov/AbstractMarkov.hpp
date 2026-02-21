#pragma once

#include <vector>

#include "kusai/graph/AbstractGraph.hpp"

class AbstractMarkov : public Serializable {
 public:
  ~AbstractMarkov() override = default;

  AbstractGraph& graph;

  virtual void train(const std::vector<std::vector<NodeId> >& sequences) = 0;

  [[nodiscard]] virtual std::optional<NodeId> nextNode(const std::vector<NodeId>& context) const = 0;

  [[nodiscard]] std::vector<NodeId> generateNodes(const std::vector<NodeId>& context, uint32_t limit = INT8_MAX) const;

 protected:
  explicit AbstractMarkov(AbstractGraph& graph) : graph(graph) {}
};
