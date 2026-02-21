#include "kusai/graph/AbstractGraph.hpp"

#include <functional>
#include <optional>
#include <string>
#include <utility>

#include "kusai/graph/Edge.hpp"
#include "kusai/graph/Node.hpp"

bool AbstractGraph::hasEdge(const NodeId source, const NodeId target) {
  const auto id = Edge::makeId(source, target);

  return hasEdge(id);
}

EdgeId AbstractGraph::addEdge(const NodeId source, const NodeId target, const std::function<void(Edge&)>& fn) {
  const auto id = Edge::makeId(source, target);

  return addEdge(id, fn);
}

NodeId AbstractGraph::ensureNode(const NodeId id, const std::function<void(Node&)>& fn) {
  if (!hasNode(id)) addNode(id, fn);

  return id;
}

EdgeId AbstractGraph::ensureEdge(const EdgeId id, const std::function<void(Edge&)>& fn) {
  if (!hasEdge(id)) addEdge(id, fn);

  return id;
}

EdgeId AbstractGraph::ensureEdge(const NodeId source, const NodeId target, const std::function<void(Edge&)>& fn) {
  const auto id = Edge::makeId(source, target);

  return ensureEdge(id, fn);
}

std::optional<Edge> AbstractGraph::getEdge(const NodeId source, const NodeId target) const {
  const auto id = Edge::makeId(source, target);

  return getEdge(id);
}

bool AbstractGraph::modifyEdge(const NodeId source, const NodeId target, std::function<void(Edge&)> fn) {
  const auto id = Edge::makeId(source, target);

  return modifyEdge(id, std::move(fn));
}

void AbstractGraph::clear() {
  clearNodes();
  clearEdges();
}

void AbstractGraph::serialize(pugi::xml_node& self) const {
  for (auto nodesNode = self.append_child("Nodes"); const auto& node : getAllNodes()) {
    node.serializeToParent(nodesNode);
  }

  for (auto edgesNode = self.append_child("Edges"); const auto& edge : getAllEdges()) {
    edge.serializeToParent(edgesNode);
  }
}

void AbstractGraph::deserialize(const pugi::xml_node& self) {
  clear();

  for (auto& nodeNode : self.child("Nodes").children()) {
    Node node;
    node.deserialize(nodeNode);

    ensureNode(node.id, [&](Node& n) { n = node; });
  }

  for (auto& edgeNode : self.child("Edges").children("Edge")) {
    Edge edge;
    edge.deserialize(edgeNode);

    ensureEdge(edge.source, edge.target, [&](Edge& e) { e = edge; });
  }
}

std::string AbstractGraph::tagName() const { return "AbstractGraph"; }
