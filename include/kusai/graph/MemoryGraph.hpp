#pragma once

#include <absl/container/flat_hash_map.h>

#include "AbstractGraph.hpp"

class MemoryGraph : public AbstractGraph {
 public:
  explicit MemoryGraph() : AbstractGraph() {}

  bool hasNode(NodeId id) override;

  bool hasEdge(EdgeId id) override;

  NodeId addNode(NodeId id, std::function<void(Node&)> fn) override;

  EdgeId addEdge(EdgeId id, std::function<void(Edge&)> fn) override;

  [[nodiscard]] std::optional<Node> getNode(NodeId id) const override;

  [[nodiscard]] std::optional<Edge> getEdge(EdgeId id) const override;

  bool modifyNode(NodeId id, std::function<void(Node&)> fn) override;

  bool modifyEdge(EdgeId id, std::function<void(Edge&)> fn) override;

  [[nodiscard]] std::vector<NodeId> getAllNodeIds() const override;

  [[nodiscard]] std::vector<EdgeId> getAllEdgeIds() const override;

  [[nodiscard]] std::vector<EdgeId> getIncomingEdgeIds(NodeId target) const override;

  [[nodiscard]] std::vector<EdgeId> getOutgoingEdgeIds(NodeId source) const override;

  [[nodiscard]] std::vector<Node> getAllNodes() const override;

  [[nodiscard]] std::vector<Edge> getAllEdges() const override;

  [[nodiscard]] std::vector<Edge> getIncomingEdges(NodeId target) const override;

  [[nodiscard]] std::vector<Edge> getOutgoingEdges(NodeId source) const override;

  void clearNodes() override;

  void clearEdges() override;

 private:
  absl::flat_hash_map<NodeId, std::unique_ptr<Node> > nodes_;
  absl::flat_hash_map<EdgeId, std::unique_ptr<Edge> > edges_;
};
