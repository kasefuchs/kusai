#pragma once

#include <absl/numeric/int128.h>

#include <optional>
#include <pugixml.hpp>

#include "Edge.hpp"
#include "Node.hpp"
#include "kusai/common/Serializable.hpp"

class AbstractGraph : public Serializable {
 public:
  ~AbstractGraph() override = default;

  virtual bool hasNode(NodeId id) = 0;

  virtual bool hasEdge(EdgeId id) = 0;

  bool hasEdge(NodeId source, NodeId target);

  virtual NodeId addNode(NodeId id, std::function<void(Node&)> fn) = 0;

  virtual EdgeId addEdge(EdgeId id, std::function<void(Edge&)> fn) = 0;

  EdgeId addEdge(NodeId source, NodeId target, const std::function<void(Edge&)>& fn = nullptr);

  NodeId ensureNode(NodeId id, const std::function<void(Node&)>& fn = nullptr);

  EdgeId ensureEdge(EdgeId id, const std::function<void(Edge&)>& fn = nullptr);

  EdgeId ensureEdge(NodeId source, NodeId target, const std::function<void(Edge&)>& fn = nullptr);

  [[nodiscard]] virtual std::optional<Node> getNode(NodeId id) const = 0;

  [[nodiscard]] virtual std::optional<Edge> getEdge(EdgeId id) const = 0;

  [[nodiscard]] std::optional<Edge> getEdge(NodeId source, NodeId target) const;

  virtual bool modifyNode(NodeId id, std::function<void(Node&)> fn) = 0;

  virtual bool modifyEdge(EdgeId id, std::function<void(Edge&)> fn) = 0;

  bool modifyEdge(NodeId source, NodeId target, std::function<void(Edge&)> fn);

  [[nodiscard]] virtual std::vector<NodeId> getAllNodeIds() const = 0;

  [[nodiscard]] virtual std::vector<EdgeId> getAllEdgeIds() const = 0;

  [[nodiscard]] virtual std::vector<EdgeId> getIncomingEdgeIds(NodeId target) const = 0;

  [[nodiscard]] virtual std::vector<EdgeId> getOutgoingEdgeIds(NodeId source) const = 0;

  [[nodiscard]] virtual std::vector<Node> getAllNodes() const = 0;

  [[nodiscard]] virtual std::vector<Edge> getAllEdges() const = 0;

  [[nodiscard]] virtual std::vector<Edge> getIncomingEdges(NodeId target) const = 0;

  [[nodiscard]] virtual std::vector<Edge> getOutgoingEdges(NodeId source) const = 0;

  virtual void clearNodes() = 0;

  virtual void clearEdges() = 0;

  void clear();

  void serialize(pugi::xml_node& self) const override;

  void deserialize(const pugi::xml_node& self) override;

  [[nodiscard]] std::string tagName() const override;

 protected:
  explicit AbstractGraph() = default;
};
