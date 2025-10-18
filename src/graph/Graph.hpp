// Copyright (c) Kasefuchs
// SPDX-License-Identifier: MIT

#pragma once

#include <graph.pb.h>

class Graph {
public:
  Graph() = default;

  ~Graph() = default;

  graph::Node *addNode();

  graph::Edge *addEdge(const graph::Node *source, const graph::Node *target);

  void serialize(graph::Graph *out) const;

  void deserialize(const graph::Graph *in);

  [[nodiscard]] std::string toD2() const;

private:
  uint32_t lastId_ = 1;

  std::vector<std::unique_ptr<graph::Node> > nodes_;
  std::vector<std::unique_ptr<graph::Edge> > edges_;
};
