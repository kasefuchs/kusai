#pragma once

#include <absl/numeric/int128.h>

#include <optional>
#include <pugixml.hpp>
#include <shared_mutex>

#include "Edge.hpp"
#include "Node.hpp"
#include "kusai/common/Serializable.hpp"

namespace kusai {
class AbstractGraph : public Serializable {
 public:
  ~AbstractGraph() override = default;

  bool hasNode(NodeId id) const;
  bool hasEdge(EdgeId id) const;
  bool hasEdge(NodeId source, NodeId target) const;

  NodeId addNode(NodeId id, const std::function<void(Node&)>& fn);
  EdgeId addEdge(EdgeId id, const std::function<void(Edge&)>& fn);
  EdgeId addEdge(NodeId source, NodeId target, const std::function<void(Edge&)>& fn = nullptr);

  NodeId ensureNode(NodeId id, const std::function<void(Node&)>& fn = nullptr);
  EdgeId ensureEdge(EdgeId id, const std::function<void(Edge&)>& fn = nullptr);
  EdgeId ensureEdge(NodeId source, NodeId target, const std::function<void(Edge&)>& fn = nullptr);

  [[nodiscard]] std::optional<Node> getNode(NodeId id) const;
  [[nodiscard]] std::optional<Edge> getEdge(EdgeId id) const;
  [[nodiscard]] std::optional<Edge> getEdge(NodeId source, NodeId target) const;

  bool modifyNode(NodeId id, const std::function<void(Node&)>& fn);
  bool modifyEdge(EdgeId id, const std::function<void(Edge&)>& fn);
  bool modifyEdge(NodeId source, NodeId target, const std::function<void(Edge&)>& fn);

  [[nodiscard]] std::vector<NodeId> getAllNodeIds() const;
  [[nodiscard]] std::vector<EdgeId> getAllEdgeIds() const;
  [[nodiscard]] std::vector<EdgeId> getIncomingEdgeIds(NodeId target) const;
  [[nodiscard]] std::vector<EdgeId> getOutgoingEdgeIds(NodeId source) const;

  [[nodiscard]] std::vector<Node> getAllNodes() const;
  [[nodiscard]] std::vector<Edge> getAllEdges() const;
  [[nodiscard]] std::vector<Edge> getIncomingEdges(NodeId target) const;
  [[nodiscard]] std::vector<Edge> getOutgoingEdges(NodeId source) const;

  void clearNodes();
  void clearEdges();
  void clear();

  void serialize(pugi::xml_node& self) const override;
  void deserialize(const pugi::xml_node& self) override;

 protected:
  mutable std::shared_mutex mutex_;

  explicit AbstractGraph() = default;

  virtual bool hasNodeUnlocked(NodeId id) const = 0;
  virtual bool hasEdgeUnlocked(EdgeId id) const = 0;
  bool hasEdgeUnlocked(NodeId source, NodeId target) const;

  virtual NodeId addNodeUnlocked(NodeId id, const std::function<void(Node&)>& fn) = 0;
  virtual EdgeId addEdgeUnlocked(EdgeId id, const std::function<void(Edge&)>& fn) = 0;
  EdgeId addEdgeUnlocked(NodeId source, NodeId target, const std::function<void(Edge&)>& fn = nullptr);

  [[nodiscard]] virtual std::optional<Node> getNodeUnlocked(NodeId id) const = 0;
  [[nodiscard]] virtual std::optional<Edge> getEdgeUnlocked(EdgeId id) const = 0;
  [[nodiscard]] std::optional<Edge> getEdgeUnlocked(NodeId source, NodeId target) const;

  virtual bool modifyNodeUnlocked(NodeId id, std::function<void(Node&)> fn) = 0;
  virtual bool modifyEdgeUnlocked(EdgeId id, std::function<void(Edge&)> fn) = 0;
  bool modifyEdgeUnlocked(NodeId source, NodeId target, const std::function<void(Edge&)>& fn);

  [[nodiscard]] virtual std::vector<NodeId> getAllNodeIdsUnlocked() const = 0;
  [[nodiscard]] virtual std::vector<EdgeId> getAllEdgeIdsUnlocked() const = 0;
  [[nodiscard]] virtual std::vector<EdgeId> getIncomingEdgeIdsUnlocked(NodeId target) const = 0;
  [[nodiscard]] virtual std::vector<EdgeId> getOutgoingEdgeIdsUnlocked(NodeId source) const = 0;

  [[nodiscard]] virtual std::vector<Node> getAllNodesUnlocked() const = 0;
  [[nodiscard]] virtual std::vector<Edge> getAllEdgesUnlocked() const = 0;
  [[nodiscard]] virtual std::vector<Edge> getIncomingEdgesUnlocked(NodeId target) const = 0;
  [[nodiscard]] virtual std::vector<Edge> getOutgoingEdgesUnlocked(NodeId source) const = 0;

  virtual void clearNodesUnlocked() = 0;
  virtual void clearEdgesUnlocked() = 0;
  void clearUnlocked();

  [[nodiscard]] std::string tagName() const override;
};
}  // namespace kusai
