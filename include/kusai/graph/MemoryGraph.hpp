#pragma once

#include <absl/container/flat_hash_map.h>

#include "AbstractGraph.hpp"

namespace kusai {
class MemoryGraph : public AbstractGraph {
 public:
  explicit MemoryGraph() : AbstractGraph() {}

 protected:
  bool hasNodeUnlocked(NodeId id) const override;
  bool hasEdgeUnlocked(EdgeId id) const override;

  NodeId addNodeUnlocked(NodeId id, const std::function<void(Node&)>& fn) override;
  EdgeId addEdgeUnlocked(EdgeId id, const std::function<void(Edge&)>& fn) override;

  [[nodiscard]] std::optional<Node> getNodeUnlocked(NodeId id) const override;
  [[nodiscard]] std::optional<Edge> getEdgeUnlocked(EdgeId id) const override;

  bool modifyNodeUnlocked(NodeId id, std::function<void(Node&)> fn) override;
  bool modifyEdgeUnlocked(EdgeId id, std::function<void(Edge&)> fn) override;

  [[nodiscard]] std::vector<NodeId> getAllNodeIdsUnlocked() const override;
  [[nodiscard]] std::vector<EdgeId> getAllEdgeIdsUnlocked() const override;
  [[nodiscard]] std::vector<EdgeId> getIncomingEdgeIdsUnlocked(NodeId target) const override;
  [[nodiscard]] std::vector<EdgeId> getOutgoingEdgeIdsUnlocked(NodeId source) const override;

  [[nodiscard]] std::vector<Node> getAllNodesUnlocked() const override;
  [[nodiscard]] std::vector<Edge> getAllEdgesUnlocked() const override;
  [[nodiscard]] std::vector<Edge> getIncomingEdgesUnlocked(NodeId target) const override;
  [[nodiscard]] std::vector<Edge> getOutgoingEdgesUnlocked(NodeId source) const override;

  void clearNodesUnlocked() override;
  void clearEdgesUnlocked() override;

 private:
  absl::flat_hash_map<NodeId, std::unique_ptr<Node> > nodes_;
  absl::flat_hash_map<EdgeId, std::unique_ptr<Edge> > edges_;
};
}  // namespace kusai
