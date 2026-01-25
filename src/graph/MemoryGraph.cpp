#include "MemoryGraph.hpp"

#include <functional>
#include <memory>
#include <optional>
#include <ranges>
#include <utility>
#include <vector>

#include "AbstractGraph.hpp"
#include "graph.pb.h"

bool MemoryGraph::hasNode(const NodeId id) { return nodes_.contains(id); }

bool MemoryGraph::hasEdge(const EdgeId id) { return edges_.contains(id); }

NodeId MemoryGraph::addNode(const NodeId id, const std::function<void(graph::Node&)> fn) {
  auto node = std::make_unique<graph::Node>();
  node->set_id(id);

  if (fn) fn(*node);
  nodes_.emplace(id, std::move(node));

  return id;
}

EdgeId MemoryGraph::addEdge(const EdgeId id, const std::function<void(graph::Edge&)> fn) {
  const auto [source, target] = splitEdgeId(id);

  auto edge = std::make_unique<graph::Edge>();
  edge->set_source(source);
  edge->set_target(target);

  if (fn) fn(*edge);
  edges_.emplace(id, std::move(edge));

  return id;
}

std::optional<graph::Node> MemoryGraph::getNode(const NodeId id) const {
  if (const auto it = nodes_.find(id); it != nodes_.end()) {
    return *it->second;
  }

  return std::nullopt;
}

std::optional<graph::Edge> MemoryGraph::getEdge(const EdgeId id) const {
  if (const auto it = edges_.find(id); it != edges_.end()) {
    return *it->second;
  }

  return std::nullopt;
}

bool MemoryGraph::modifyNode(const NodeId id, const std::function<void(graph::Node&)> fn) {
  if (const auto it = nodes_.find(id); it != nodes_.end()) {
    fn(*it->second);

    return true;
  }

  return false;
}

bool MemoryGraph::modifyEdge(const EdgeId id, const std::function<void(graph::Edge&)> fn) {
  if (const auto it = edges_.find(id); it != edges_.end()) {
    fn(*it->second);

    return true;
  }

  return false;
}

std::vector<NodeId> MemoryGraph::getAllNodeIds() const {
  const auto view = std::views::keys(nodes_);

  return {view.begin(), view.end()};
}

std::vector<EdgeId> MemoryGraph::getAllEdgeIds() const {
  const auto view = std::views::keys(edges_);

  return {view.begin(), view.end()};
}

std::vector<EdgeId> MemoryGraph::getIncomingEdgeIds(NodeId target) const {
  auto view = edges_ | std::views::values | std::views::filter([&](const auto& e) { return e->target() == target; }) |
              std::views::transform([](const auto& e) { return makeEdgeId(e->source(), e->target()); });

  return {view.begin(), view.end()};
}

std::vector<EdgeId> MemoryGraph::getOutgoingEdgeIds(NodeId source) const {
  auto view = edges_ | std::views::values | std::views::filter([&](const auto& e) { return e->source() == source; }) |
              std::views::transform([](const auto& e) { return makeEdgeId(e->source(), e->target()); });

  return {view.begin(), view.end()};
}

std::vector<graph::Node> MemoryGraph::getAllNodes() const {
  const auto view = std::views::values(nodes_) | std::views::transform([](const auto& p) { return *p; });

  return {view.begin(), view.end()};
}

std::vector<graph::Edge> MemoryGraph::getAllEdges() const {
  const auto view = std::views::values(edges_) | std::views::transform([](const auto& p) { return *p; });

  return {view.begin(), view.end()};
}

std::vector<graph::Edge> MemoryGraph::getIncomingEdges(NodeId target) const {
  auto view = edges_ | std::views::values | std::views::filter([&](const auto& e) { return e->target() == target; }) |
              std::views::transform([](const auto& p) { return *p; });

  return {view.begin(), view.end()};
}

std::vector<graph::Edge> MemoryGraph::getOutgoingEdges(NodeId source) const {
  auto view = edges_ | std::views::values | std::views::filter([&](const auto& e) { return e->source() == source; }) |
              std::views::transform([](const auto& p) { return *p; });

  return {view.begin(), view.end()};
}

void MemoryGraph::clearNodes() { nodes_.clear(); }

void MemoryGraph::clearEdges() { edges_.clear(); }
