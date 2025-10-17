// Copyright (c) Kasefuchs
// SPDX-License-Identifier: MIT

#pragma once

#include <graph.pb.h>

#include "Edge.hpp"
#include "Node.hpp"

class Graph {
public:
  Graph() = default;

  ~Graph() = default;

  Node* addNode();

  Edge* addEdge(const Node* source, const Node* target);

  void serialize(graph::Graph *out) const;

  void deserialize(const graph::Graph *in);

  std::string toD2() const;

private:
  uint32_t lastId_ = 1;

  std::vector<std::unique_ptr<Node> > nodes_;
  std::vector<std::unique_ptr<Edge> > edges_;
};
