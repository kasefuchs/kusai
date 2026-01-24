#pragma once

#include <vector>

#include "AbstractGraph.hpp"
#include "graph.pb.h"

class AbstractMarkov {
 public:
  virtual ~AbstractMarkov() = default;

  AbstractGraph& graph;

  virtual void train(const std::vector<std::vector<NodeId>>& sequences) = 0;

  [[nodiscard]] virtual std::optional<NodeId> nextNode(const std::vector<NodeId>& context) const = 0;

  virtual void serialize(google::protobuf::Any& out) const = 0;

  virtual void deserialize(const google::protobuf::Any& in) = 0;

  [[nodiscard]] std::vector<NodeId> generateNodes(const std::vector<NodeId>& context, uint32_t limit = INT8_MAX) const;

  void serializeToOstream(std::ostream& out) const;

  void deserializeFromIstream(std::istream& in);

 protected:
  explicit AbstractMarkov(AbstractGraph& graph) : graph(graph) {}
};
