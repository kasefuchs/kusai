#include "PyAbstractGraph.hpp"

namespace kusai::bind::python {
nlohmann::json PyAbstractGraph::serialize() const { PYBIND11_OVERRIDE(nlohmann::json, AbstractGraph, serialize); }

bool PyAbstractGraph::deserialize(const nlohmann::json& data) {
  PYBIND11_OVERRIDE(bool, AbstractGraph, deserialize, data);
}

bool PyAbstractGraph::hasNodeUnlocked(NodeId id) const {
  PYBIND11_OVERRIDE_PURE_NAME(bool, AbstractGraph, "_has_node_unlocked", hasNodeUnlocked, id);
}

bool PyAbstractGraph::hasEdgeUnlocked(EdgeId id) const {
  PYBIND11_OVERRIDE_PURE_NAME(bool, AbstractGraph, "_has_edge_unlocked", hasEdgeUnlocked, id);
}

NodeId PyAbstractGraph::addNodeUnlocked(NodeId id, const std::function<void(Node&)>& fn) {
  PYBIND11_OVERRIDE_PURE_NAME(NodeId, AbstractGraph, "_add_node_unlocked", addNodeUnlocked, id, fn);
}

EdgeId PyAbstractGraph::addEdgeUnlocked(NodeId source, NodeId target, const std::function<void(Edge&)>& fn) {
  PYBIND11_OVERRIDE_PURE_NAME(EdgeId, AbstractGraph, "_add_edge_unlocked", addEdgeUnlocked, source, target, fn);
}

std::optional<Node> PyAbstractGraph::getNodeUnlocked(NodeId id) const {
  PYBIND11_OVERRIDE_PURE_NAME(std::optional<Node>, AbstractGraph, "_get_node_unlocked", getNodeUnlocked, id);
}

std::optional<Edge> PyAbstractGraph::getEdgeUnlocked(EdgeId id) const {
  PYBIND11_OVERRIDE_PURE_NAME(std::optional<Edge>, AbstractGraph, "_get_edge_unlocked", getEdgeUnlocked, id);
}

bool PyAbstractGraph::modifyNodeUnlocked(NodeId id, std::function<void(Node&)> fn) {
  PYBIND11_OVERRIDE_PURE_NAME(bool, AbstractGraph, "_modify_node_unlocked", modifyNodeUnlocked, id, fn);
}

bool PyAbstractGraph::modifyEdgeUnlocked(EdgeId id, std::function<void(Edge&)> fn) {
  PYBIND11_OVERRIDE_PURE_NAME(bool, AbstractGraph, "_modify_edge_unlocked", modifyEdgeUnlocked, id, fn);
}

std::vector<NodeId> PyAbstractGraph::getAllNodeIdsUnlocked() const {
  PYBIND11_OVERRIDE_PURE_NAME(std::vector<NodeId>, AbstractGraph, "_get_all_node_ids_unlocked", getAllNodeIdsUnlocked);
}

std::vector<EdgeId> PyAbstractGraph::getAllEdgeIdsUnlocked() const {
  PYBIND11_OVERRIDE_PURE_NAME(std::vector<EdgeId>, AbstractGraph, "_get_all_edge_ids_unlocked", getAllEdgeIdsUnlocked);
}

std::vector<EdgeId> PyAbstractGraph::getIncomingEdgeIdsUnlocked(NodeId target) const {
  PYBIND11_OVERRIDE_PURE_NAME(std::vector<EdgeId>, AbstractGraph, "_get_incoming_edge_ids_unlocked",
                              getIncomingEdgeIdsUnlocked, target);
}

std::vector<EdgeId> PyAbstractGraph::getOutgoingEdgeIdsUnlocked(NodeId source) const {
  PYBIND11_OVERRIDE_PURE_NAME(std::vector<EdgeId>, AbstractGraph, "_get_outgoing_edge_ids_unlocked",
                              getOutgoingEdgeIdsUnlocked, source);
}

std::vector<Node> PyAbstractGraph::getAllNodesUnlocked() const {
  PYBIND11_OVERRIDE_PURE_NAME(std::vector<Node>, AbstractGraph, "_get_all_nodes_unlocked", getAllNodesUnlocked);
}

std::vector<Edge> PyAbstractGraph::getAllEdgesUnlocked() const {
  PYBIND11_OVERRIDE_PURE_NAME(std::vector<Edge>, AbstractGraph, "_get_all_edges_unlocked", getAllEdgesUnlocked);
}

std::vector<Edge> PyAbstractGraph::getIncomingEdgesUnlocked(NodeId target) const {
  PYBIND11_OVERRIDE_PURE_NAME(std::vector<Edge>, AbstractGraph, "_get_incoming_edges_unlocked",
                              getIncomingEdgesUnlocked, target);
}

std::vector<Edge> PyAbstractGraph::getOutgoingEdgesUnlocked(NodeId source) const {
  PYBIND11_OVERRIDE_PURE_NAME(std::vector<Edge>, AbstractGraph, "_get_outgoing_edges_unlocked",
                              getOutgoingEdgesUnlocked, source);
}

void PyAbstractGraph::clearNodesUnlocked() {
  PYBIND11_OVERRIDE_PURE_NAME(void, AbstractGraph, "_clear_nodes_unlocked", clearNodesUnlocked);
}

void PyAbstractGraph::clearEdgesUnlocked() {
  PYBIND11_OVERRIDE_PURE_NAME(void, AbstractGraph, "_clear_edges_unlocked", clearEdgesUnlocked);
}
}  // namespace kusai::bind::python
