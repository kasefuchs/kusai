#include "kusai/graph/AbstractGraph.hpp"

#include <functional>
#include <mutex>
#include <optional>
#include <string>
#include <utility>

#include "kusai/graph/Edge.hpp"
#include "kusai/graph/Node.hpp"

namespace kusai {
bool AbstractGraph::hasNode(const NodeId id) const {
  std::shared_lock lock(mutex_);
  return hasNodeUnlocked(id);
}

bool AbstractGraph::hasEdge(const EdgeId id) const {
  std::shared_lock lock(mutex_);
  return hasEdgeUnlocked(id);
}

bool AbstractGraph::hasEdge(const NodeId source, const NodeId target) const {
  std::shared_lock lock(mutex_);
  return hasEdgeUnlocked(source, target);
}

NodeId AbstractGraph::addNode(const NodeId id, const std::function<void(Node&)>& fn) {
  std::unique_lock lock(mutex_);
  return addNodeUnlocked(id, fn);
}

EdgeId AbstractGraph::addEdge(const NodeId source, const NodeId target, const std::function<void(Edge&)>& fn) {
  std::unique_lock lock(mutex_);
  return addEdgeUnlocked(source, target, fn);
}

NodeId AbstractGraph::ensureNode(const NodeId id, const std::function<void(Node&)>& fn) {
  std::unique_lock lock(mutex_);
  if (!hasNodeUnlocked(id)) addNodeUnlocked(id, fn);

  return id;
}

EdgeId AbstractGraph::ensureEdge(const NodeId source, const NodeId target, const std::function<void(Edge&)>& fn) {
  const auto id = Edge::makeId(source, target);
  if (!hasEdgeUnlocked(id)) addEdgeUnlocked(source, target, fn);

  return id;
}

std::optional<Node> AbstractGraph::getNode(const NodeId id) const {
  std::shared_lock lock(mutex_);
  return getNodeUnlocked(id);
}

std::optional<Edge> AbstractGraph::getEdge(const EdgeId id) const {
  std::shared_lock lock(mutex_);
  return getEdgeUnlocked(id);
}

std::optional<Edge> AbstractGraph::getEdge(const NodeId source, const NodeId target) const {
  std::shared_lock lock(mutex_);
  return getEdgeUnlocked(source, target);
}

bool AbstractGraph::modifyNode(const NodeId id, const std::function<void(Node&)>& fn) {
  std::unique_lock lock(mutex_);
  return modifyNodeUnlocked(id, fn);
}

bool AbstractGraph::modifyEdge(const EdgeId id, const std::function<void(Edge&)>& fn) {
  std::unique_lock lock(mutex_);
  return modifyEdgeUnlocked(id, fn);
}

bool AbstractGraph::modifyEdge(const NodeId source, const NodeId target, const std::function<void(Edge&)>& fn) {
  std::unique_lock lock(mutex_);
  return modifyEdgeUnlocked(source, target, fn);
}

std::vector<NodeId> AbstractGraph::getAllNodeIds() const {
  std::shared_lock lock(mutex_);
  return getAllNodeIdsUnlocked();
}

std::vector<EdgeId> AbstractGraph::getAllEdgeIds() const {
  std::shared_lock lock(mutex_);
  return getAllEdgeIdsUnlocked();
}

std::vector<EdgeId> AbstractGraph::getIncomingEdgeIds(const NodeId target) const {
  std::shared_lock lock(mutex_);
  return getIncomingEdgeIdsUnlocked(target);
}

std::vector<EdgeId> AbstractGraph::getOutgoingEdgeIds(const NodeId source) const {
  std::shared_lock lock(mutex_);
  return getOutgoingEdgeIdsUnlocked(source);
}

std::vector<Node> AbstractGraph::getAllNodes() const {
  std::shared_lock lock(mutex_);
  return getAllNodesUnlocked();
}

std::vector<Edge> AbstractGraph::getAllEdges() const {
  std::shared_lock lock(mutex_);
  return getAllEdgesUnlocked();
}

std::vector<Edge> AbstractGraph::getIncomingEdges(const NodeId target) const {
  std::shared_lock lock(mutex_);
  return getIncomingEdgesUnlocked(target);
}

std::vector<Edge> AbstractGraph::getOutgoingEdges(const NodeId source) const {
  std::shared_lock lock(mutex_);
  return getOutgoingEdgesUnlocked(source);
}

void AbstractGraph::clearNodes() {
  std::unique_lock lock(mutex_);
  clearNodesUnlocked();
}

void AbstractGraph::clearEdges() {
  std::unique_lock lock(mutex_);
  clearEdgesUnlocked();
}

void AbstractGraph::clear() {
  std::unique_lock lock(mutex_);
  clearUnlocked();
}

void AbstractGraph::serialize(pugi::xml_node& self) const {
  std::shared_lock lock(mutex_);
  for (auto nodesNode = self.append_child("Nodes"); const auto& node : getAllNodes()) {
    node.serializeToParent(nodesNode);
  }

  for (auto edgesNode = self.append_child("Edges"); const auto& edge : getAllEdges()) {
    edge.serializeToParent(edgesNode);
  }
}

void AbstractGraph::deserialize(const pugi::xml_node& self) {
  std::unique_lock lock(mutex_);
  clearUnlocked();

  for (auto& nodeNode : self.child("Nodes").children()) {
    Node node;
    node.deserialize(nodeNode);

    addNodeUnlocked(node.id, [&](Node& n) { n = node; });
  }

  for (auto& edgeNode : self.child("Edges").children("Edge")) {
    Edge edge;
    edge.deserialize(edgeNode);

    addEdgeUnlocked(edge.source, edge.target, [&](Edge& e) { e = edge; });
  }
}

std::string AbstractGraph::tagName() const { return "AbstractGraph"; }

bool AbstractGraph::hasEdgeUnlocked(const NodeId source, const NodeId target) const {
  const auto id = Edge::makeId(source, target);
  return hasEdgeUnlocked(id);
}

std::optional<Edge> AbstractGraph::getEdgeUnlocked(const NodeId source, const NodeId target) const {
  const auto id = Edge::makeId(source, target);
  return getEdgeUnlocked(id);
}

bool AbstractGraph::modifyEdgeUnlocked(const NodeId source, const NodeId target, const std::function<void(Edge&)>& fn) {
  const auto id = Edge::makeId(source, target);
  return modifyEdgeUnlocked(id, fn);
}

void AbstractGraph::clearUnlocked() {
  clearEdgesUnlocked();
  clearNodesUnlocked();
}
}  // namespace kusai
