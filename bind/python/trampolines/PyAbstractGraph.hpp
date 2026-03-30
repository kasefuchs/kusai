#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// ReSharper disable once CppUnusedIncludeDirective
#include <pybind11_json/pybind11_json.hpp>

#include "kusai/graph/AbstractGraph.hpp"

namespace kusai::bind::python {
class PyAbstractGraph : public AbstractGraph {
 public:
  [[nodiscard]] nlohmann::json serialize() const override;
  bool deserialize(const nlohmann::json& data) override;

  bool hasNodeUnlocked(NodeId id) const override;
  bool hasEdgeUnlocked(EdgeId id) const override;

  NodeId addNodeUnlocked(NodeId id, const std::function<void(Node&)>& fn) override;
  EdgeId addEdgeUnlocked(NodeId source, NodeId target, const std::function<void(Edge&)>& fn) override;

  std::optional<Node> getNodeUnlocked(NodeId id) const override;
  std::optional<Edge> getEdgeUnlocked(EdgeId id) const override;

  bool modifyNodeUnlocked(NodeId id, std::function<void(Node&)> fn) override;
  bool modifyEdgeUnlocked(EdgeId id, std::function<void(Edge&)> fn) override;

  std::vector<NodeId> getAllNodeIdsUnlocked() const override;
  std::vector<EdgeId> getAllEdgeIdsUnlocked() const override;

  std::vector<EdgeId> getIncomingEdgeIdsUnlocked(NodeId target) const override;
  std::vector<EdgeId> getOutgoingEdgeIdsUnlocked(NodeId source) const override;

  std::vector<Node> getAllNodesUnlocked() const override;
  std::vector<Edge> getAllEdgesUnlocked() const override;

  std::vector<Edge> getIncomingEdgesUnlocked(NodeId target) const override;
  std::vector<Edge> getOutgoingEdgesUnlocked(NodeId source) const override;

  void clearNodesUnlocked() override;
  void clearEdgesUnlocked() override;
};
}  // namespace kusai::bind::python
