#pragma once

#include "AbstractGraph.hpp"

class MemoryGraph : public AbstractGraph {
 public:
  explicit MemoryGraph() : AbstractGraph() {}

  bool hasNode(NodeId id) override;

  bool hasEdge(EdgeId id) override;

  NodeId addNode(NodeId id) override;

  EdgeId addEdge(EdgeId id) override;

  std::optional<graph::Node> getNode(NodeId id) const override;

  std::optional<graph::Edge> getEdge(EdgeId id) const override;

  bool modifyNode(NodeId id, std::function<void(graph::Node&)> fn) override;

  bool modifyEdge(EdgeId id, std::function<void(graph::Edge&)> fn) override;

  std::vector<NodeId> getAllNodeIds() const override;

  std::vector<EdgeId> getAllEdgeIds() const override;

  std::vector<EdgeId> getIncomingEdgeIds(NodeId target) const override;

  std::vector<EdgeId> getOutgoingEdgeIds(NodeId source) const override;

  std::vector<graph::Node> getAllNodes() const override;

  std::vector<graph::Edge> getAllEdges() const override;

  std::vector<graph::Edge> getIncomingEdges(NodeId target) const override;

  std::vector<graph::Edge> getOutgoingEdges(NodeId source) const override;

  void clearNodes() override;

  void clearEdges() override;

 private:
  absl::flat_hash_map<NodeId, std::unique_ptr<graph::Node>> nodes_;
  absl::flat_hash_map<EdgeId, std::unique_ptr<graph::Edge>> edges_;
};
