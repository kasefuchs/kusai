// Copyright (c) Kasefuchs
// SPDX-License-Identifier: MIT

#include "Graph.hpp"

#include "graph.hpp"

graph::Node *Graph::addNode() {
  auto node = std::make_unique<graph::Node>();
  node->set_id(lastId_++);

  nodes_.emplace_back(std::move(node));
  return nodes_.back().get();
}

graph::Edge *Graph::addEdge(const graph::Node *source, const graph::Node *target) {
  auto edge = std::make_unique<graph::Edge>();
  edge->set_source(source->id());
  edge->set_target(target->id());

  edges_.emplace_back(std::move(edge));
  return edges_.back().get();
}

void Graph::serialize(graph::Graph *out) const {
  for (const auto &node: nodes_) {
    graph::Node *n = out->add_nodes();
    n->CopyFrom(*node);
  }

  for (const auto &edge: edges_) {
    graph::Edge *e = out->add_edges();
    e->CopyFrom(*edge);
  }
}

void Graph::deserialize(const graph::Graph *in) {
  lastId_ = 1;
  nodes_.clear();
  edges_.clear();

  std::unordered_map<uint32_t, graph::Node *> idToNode;

  for (const auto &nodeProto: in->nodes()) {
    graph::Node *n = addNode();
    n->CopyFrom(nodeProto);
    idToNode[n->id()] = n;
  }

  for (const auto &edgeProto: in->edges()) {
    const auto itSrc = idToNode.find(edgeProto.source());
    const auto itDst = idToNode.find(edgeProto.target());

    addEdge(itSrc->second, itDst->second);
  }
}

std::string Graph::toD2() const {
  std::ostringstream buf;

  for (const auto &node: nodes_) {
    buf << graph::toD2(*node) << std::endl;
  }

  for (const auto &edge: edges_) {
    buf << graph::toD2(*edge) << std::endl;
  }

  return buf.str();
}
