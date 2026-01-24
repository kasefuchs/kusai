#include "AbstractGraph.hpp"

#include <absl/numeric/int128.h>

#include <functional>
#include <optional>
#include <utility>

#include "graph.pb.h"

bool AbstractGraph::hasEdge(const NodeId source, const NodeId target) {
  const auto id = makeEdgeId(source, target);

  return hasEdge(id);
}

EdgeId AbstractGraph::addEdge(const NodeId source, const NodeId target) {
  const auto id = makeEdgeId(source, target);

  return addEdge(id);
}

NodeId AbstractGraph::ensureNode(const NodeId id) {
  if (!hasNode(id)) {
    addNode(id);
  }

  return id;
}

EdgeId AbstractGraph::ensureEdge(const EdgeId id) {
  if (!hasEdge(id)) {
    addEdge(id);
  }

  return id;
}

EdgeId AbstractGraph::ensureEdge(const NodeId source, const NodeId target) {
  const auto id = makeEdgeId(source, target);

  return ensureEdge(id);
}

std::optional<graph::Edge> AbstractGraph::getEdge(const NodeId source, const NodeId target) const {
  const auto id = makeEdgeId(source, target);

  return getEdge(id);
}

bool AbstractGraph::modifyEdge(const NodeId source, const NodeId target, std::function<void(graph::Edge&)> fn) {
  const auto id = makeEdgeId(source, target);

  return modifyEdge(id, std::move(fn));
}

void AbstractGraph::clear() {
  clearNodes();
  clearEdges();
}

void AbstractGraph::serialize(graph::Graph& out) const {
  for (const auto& node : getAllNodes()) out.add_nodes()->CopyFrom(node);

  for (const auto& edge : getAllEdges()) out.add_edges()->CopyFrom(edge);
}

void AbstractGraph::deserialize(const graph::Graph& in) {
  clear();

  for (const auto& node : in.nodes()) {
    ensureNode(node.id());
    modifyNode(node.id(), [&](graph::Node& n) { n.CopyFrom(node); });
  }

  for (const auto& edge : in.edges()) {
    ensureEdge(edge.source(), edge.target());
    modifyEdge(edge.source(), edge.target(), [&](graph::Edge& e) { e.CopyFrom(edge); });
  }
}

absl::uint128 AbstractGraph::makeEdgeId(const NodeId source, const NodeId target) {
  return absl::MakeUint128(source, target);
}

std::pair<NodeId, NodeId> AbstractGraph::splitEdgeId(const EdgeId id) {
  return {
      absl::Uint128High64(id),  // source
      absl::Uint128Low64(id)    // target
  };
}
