#pragma once

#include "Graph.hpp"

class AbstractMarkov {
public:
  virtual ~AbstractMarkov() = default;

  Graph &graph;

  virtual void train(const std::vector<std::vector<graph::Node *>> &sequences) = 0;

  [[nodiscard]] virtual graph::Node *nextNode(const std::vector<graph::Node *> &context) const = 0;

  virtual void serialize(google::protobuf::Any &out) const = 0;

  virtual void deserialize(const google::protobuf::Any &in) = 0;

  std::vector<graph::Node *> generateNodes(const std::vector<graph::Node *> &context, uint32_t limit = INT8_MAX) const;

  void serializeToOstream(std::ostream &out) const;

  void deserializeFromIstream(std::istream &in);

protected:
  explicit AbstractMarkov(Graph &graph) : graph(graph) {}
};
