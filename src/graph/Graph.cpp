// Copyright (c) Kasefuchs
// SPDX-License-Identifier: MIT

#include "Graph.hpp"

Node *Graph::addNode() {
  auto node = std::make_unique<Node>(lastId_++);
  nodes_.emplace_back(std::move(node));
  return nodes_.back().get();
}

Edge *Graph::addEdge(const Node *source, const Node *target) {
  auto edge = std::make_unique<Edge>(source->id(), target->id());
  edges_.emplace_back(std::move(edge));
  return edges_.back().get();
}

void Graph::serialize(graph::Graph *out) const {
  for (const auto &node: nodes_) {
    graph::Node *n = out->add_nodes();
    node->serialize(n);
  }

  for (const auto &edge: edges_) {
    graph::Edge *e = out->add_edges();
    edge->serialize(e);
  }
}

void Graph::deserialize(const graph::Graph *in) {
  std::unordered_map<uint32_t, Node *> idToNode;

  for (const auto &nodeProto: in->nodes()) {
    Node *n = addNode();
    n->deserialize(&nodeProto);

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
    buf << node->id() << std::endl;
  }

  for (const auto &edge: edges_) {
    buf << edge->sourceId() << " -> " << edge->targetId() << std::endl;
  }

  return buf.str();
}
