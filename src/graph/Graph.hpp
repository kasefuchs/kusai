// Copyright (c) Kasefuchs
// SPDX-License-Identifier: MIT

#pragma once

#include <graph.pb.h>

class Graph {
public:
  Graph() = default;

  ~Graph() = default;

  graph::Node *addNode();

  [[nodiscard]] graph::Node *getNode(uint32_t id) const;

  graph::Edge *addEdge(uint32_t source, uint32_t target);

  graph::Edge *addEdge(const graph::Node *source, const graph::Node *target);

  [[nodiscard]] graph::Edge *getEdge(uint32_t source, uint32_t target) const;

  graph::Edge *getEdge(const graph::Node *source, const graph::Node *target) const;

  std::vector<graph::Edge *> getOutgoingEdges(const graph::Node *source) const;

  graph::Edge *getOrAddEdge(uint32_t source, uint32_t target);

  graph::Edge *getOrAddEdge(const graph::Node* source, const graph::Node* target);

  void serialize(graph::Graph *out) const;

  void deserialize(const graph::Graph *in);

  [[nodiscard]] std::string toD2() const;

private:
  uint32_t lastId_ = 1;

protected:
  std::vector<std::unique_ptr<graph::Node> > nodes_;
  std::vector<std::unique_ptr<graph::Edge> > edges_;
};
