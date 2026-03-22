#include "kusai/graph/MemoryGraph.hpp"

#include <functional>
#include <memory>
#include <optional>
#include <ranges>
#include <utility>
#include <vector>

#include "kusai/graph/Edge.hpp"
#include "kusai/graph/Node.hpp"

namespace kusai {
bool MemoryGraph::hasNodeUnlocked(const NodeId id) const { return nodes_.contains(id); }

bool MemoryGraph::hasEdgeUnlocked(const EdgeId id) const { return edges_.contains(id); }

NodeId MemoryGraph::addNodeUnlocked(const NodeId id, const std::function<void(Node&)>& fn) {
  auto node = std::make_unique<Node>();
  node->id = id;

  if (fn) fn(*node);
  nodes_.emplace(id, std::move(node));

  return id;
}

EdgeId MemoryGraph::addEdgeUnlocked(const EdgeId id, const std::function<void(Edge&)>& fn) {
  const auto [source, target] = Edge::splitId(id);

  auto edge = std::make_unique<Edge>();
  edge->source = source;
  edge->target = target;

  if (fn) fn(*edge);
  edges_.emplace(id, std::move(edge));

  return id;
}

std::optional<Node> MemoryGraph::getNodeUnlocked(const NodeId id) const {
  if (const auto it = nodes_.find(id); it != nodes_.end()) {
    return *it->second;
  }

  return std::nullopt;
}

std::optional<Edge> MemoryGraph::getEdgeUnlocked(const EdgeId id) const {
  if (const auto it = edges_.find(id); it != edges_.end()) {
    return *it->second;
  }

  return std::nullopt;
}

bool MemoryGraph::modifyNodeUnlocked(const NodeId id, const std::function<void(Node&)> fn) {
  if (const auto it = nodes_.find(id); it != nodes_.end()) {
    fn(*it->second);

    return true;
  }

  return false;
}

bool MemoryGraph::modifyEdgeUnlocked(const EdgeId id, const std::function<void(Edge&)> fn) {
  if (const auto it = edges_.find(id); it != edges_.end()) {
    fn(*it->second);

    return true;
  }

  return false;
}

std::vector<NodeId> MemoryGraph::getAllNodeIdsUnlocked() const {
  const auto view = std::views::keys(nodes_);

  return {view.begin(), view.end()};
}

std::vector<EdgeId> MemoryGraph::getAllEdgeIdsUnlocked() const {
  const auto view = std::views::keys(edges_);

  return {view.begin(), view.end()};
}

std::vector<EdgeId> MemoryGraph::getIncomingEdgeIdsUnlocked(NodeId target) const {
  auto view = edges_ | std::views::values | std::views::filter([&](const auto& e) { return e->target == target; }) |
              std::views::transform([](const auto& e) { return Edge::makeId(e->source, e->target); });

  return {view.begin(), view.end()};
}

std::vector<EdgeId> MemoryGraph::getOutgoingEdgeIdsUnlocked(NodeId source) const {
  auto view = edges_ | std::views::values | std::views::filter([&](const auto& e) { return e->source == source; }) |
              std::views::transform([](const auto& e) { return Edge::makeId(e->source, e->target); });

  return {view.begin(), view.end()};
}

std::vector<Node> MemoryGraph::getAllNodesUnlocked() const {
  const auto view = std::views::values(nodes_) | std::views::transform([](const auto& p) { return *p; });

  return {view.begin(), view.end()};
}

std::vector<Edge> MemoryGraph::getAllEdgesUnlocked() const {
  const auto view = std::views::values(edges_) | std::views::transform([](const auto& p) { return *p; });

  return {view.begin(), view.end()};
}

std::vector<Edge> MemoryGraph::getIncomingEdgesUnlocked(NodeId target) const {
  auto view = edges_ | std::views::values | std::views::filter([&](const auto& e) { return e->target == target; }) |
              std::views::transform([](const auto& p) { return *p; });

  return {view.begin(), view.end()};
}

std::vector<Edge> MemoryGraph::getOutgoingEdgesUnlocked(NodeId source) const {
  auto view = edges_ | std::views::values | std::views::filter([&](const auto& e) { return e->source == source; }) |
              std::views::transform([](const auto& p) { return *p; });

  return {view.begin(), view.end()};
}

void MemoryGraph::clearNodesUnlocked() { nodes_.clear(); }

void MemoryGraph::clearEdgesUnlocked() { edges_.clear(); }
}  // namespace kusai
