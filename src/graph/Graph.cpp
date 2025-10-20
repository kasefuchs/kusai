// Copyright (c) Kasefuchs
// SPDX-License-Identifier: MIT

#include "Graph.hpp"

#include "graph.hpp"

graph::Node *Graph::addNode() {
  auto node = std::make_unique<graph::Node>();
  node->set_id(lastNodeId_++);

  const auto [it, _] = nodes_.emplace(node->id(), std::move(node));
  return it->second.get();
}

graph::Node *Graph::getNode(const uint32_t id) const {
  return nodes_.at(id).get();
}

graph::Edge *Graph::addEdge(const uint32_t source, const uint32_t target) {
  auto edge = std::make_unique<graph::Edge>();
  edge->set_source(source);
  edge->set_target(target);

  edges_.emplace_back(std::move(edge));
  return edges_.back().get();
}

graph::Edge *Graph::addEdge(const graph::Node *source, const graph::Node *target) {
  return addEdge(source->id(), target->id());
}

graph::Edge *Graph::getEdge(const uint32_t source, const uint32_t target) const {
  for (const auto &edge: edges_) {
    if (edge->source() == source && edge->target() == target) return edge.get();
  }

  return nullptr;
}

graph::Edge *Graph::getEdge(const graph::Node *source, const graph::Node *target) const {
  return getEdge(source->id(), target->id());
}

std::vector<graph::Edge *> Graph::getOutgoingEdges(const graph::Node *source) const {
  std::vector<graph::Edge *> result;
  for (const auto &edge: edges_) {
    if (edge->source() == source->id()) result.push_back(edge.get());
  }

  return result;
}

graph::Edge *Graph::getOrAddEdge(const uint32_t source, const uint32_t target) {
  if (auto *edge = getEdge(source, target)) return edge;

  return addEdge(source, target);
}

graph::Edge *Graph::getOrAddEdge(const graph::Node *source, const graph::Node *target) {
  return getOrAddEdge(source->id(), target->id());
}

void Graph::serialize(graph::Graph *out) const {
  for (const auto &[_, node]: nodes_) {
    graph::Node *n = out->add_nodes();
    n->CopyFrom(*node);
  }

  for (const auto &edge: edges_) {
    graph::Edge *e = out->add_edges();
    e->CopyFrom(*edge);
  }
}

void Graph::deserialize(const graph::Graph *in) {
  lastNodeId_ = 1;
  nodes_.clear();
  edges_.clear();

  std::unordered_map<uint32_t, uint32_t> idToNode;

  for (const auto &nodeProto: in->nodes()) {
    graph::Node *n = addNode();
    const uint32_t newId = n->id();

    n->CopyFrom(nodeProto);
    n->set_id(newId);

    idToNode[nodeProto.id()] = newId;
  }

  for (const auto &edgeProto: in->edges()) {
    addEdge(idToNode[edgeProto.source()], idToNode[edgeProto.target()]);
  }
}

std::string Graph::toD2() const {
  std::ostringstream buf;

  for (const auto &[_, node]: nodes_) {
    buf << graph::toD2(*node) << std::endl;
  }

  for (const auto &edge: edges_) {
    buf << graph::toD2(*edge) << std::endl;
  }

  return buf.str();
}
