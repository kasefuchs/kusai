#pragma once

#include <absl/numeric/int128.h>

#include <optional>

#include "kusai/proto/graph.pb.h"

using NodeId = std::uint64_t;
using EdgeId = absl::uint128;

class AbstractGraph {
 public:
  virtual ~AbstractGraph() = default;

  virtual bool hasNode(NodeId id) = 0;

  virtual bool hasEdge(EdgeId id) = 0;

  bool hasEdge(NodeId source, NodeId target);

  virtual NodeId addNode(NodeId id, std::function<void(graph::Node&)> fn) = 0;

  virtual EdgeId addEdge(EdgeId id, std::function<void(graph::Edge&)> fn) = 0;

  EdgeId addEdge(NodeId source, NodeId target, const std::function<void(graph::Edge&)>& fn = nullptr);

  NodeId ensureNode(NodeId id, const std::function<void(graph::Node&)>& fn = nullptr);

  EdgeId ensureEdge(EdgeId id, const std::function<void(graph::Edge&)>& fn = nullptr);

  EdgeId ensureEdge(NodeId source, NodeId target, const std::function<void(graph::Edge&)>& fn = nullptr);

  [[nodiscard]] virtual std::optional<graph::Node> getNode(NodeId id) const = 0;

  [[nodiscard]] virtual std::optional<graph::Edge> getEdge(EdgeId id) const = 0;

  [[nodiscard]] std::optional<graph::Edge> getEdge(NodeId source, NodeId target) const;

  virtual bool modifyNode(NodeId id, std::function<void(graph::Node&)> fn) = 0;

  virtual bool modifyEdge(EdgeId id, std::function<void(graph::Edge&)> fn) = 0;

  bool modifyEdge(NodeId source, NodeId target, std::function<void(graph::Edge&)> fn);

  [[nodiscard]] virtual std::vector<NodeId> getAllNodeIds() const = 0;

  [[nodiscard]] virtual std::vector<EdgeId> getAllEdgeIds() const = 0;

  [[nodiscard]] virtual std::vector<EdgeId> getIncomingEdgeIds(NodeId target) const = 0;

  [[nodiscard]] virtual std::vector<EdgeId> getOutgoingEdgeIds(NodeId source) const = 0;

  [[nodiscard]] virtual std::vector<graph::Node> getAllNodes() const = 0;

  [[nodiscard]] virtual std::vector<graph::Edge> getAllEdges() const = 0;

  [[nodiscard]] virtual std::vector<graph::Edge> getIncomingEdges(NodeId target) const = 0;

  [[nodiscard]] virtual std::vector<graph::Edge> getOutgoingEdges(NodeId source) const = 0;

  virtual void clearNodes() = 0;

  virtual void clearEdges() = 0;

  void clear();

  void serialize(graph::Graph& out) const;

  void deserialize(const graph::Graph& in);

  static absl::uint128 makeEdgeId(NodeId source, NodeId target);

  static std::pair<NodeId, NodeId> splitEdgeId(EdgeId id);

 protected:
  explicit AbstractGraph() = default;
};
