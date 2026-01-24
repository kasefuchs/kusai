#pragma once

#include <sw/redis++/redis++.h>

#include "AbstractGraph.hpp"

class RedisGraph : public AbstractGraph {
 public:
  explicit RedisGraph(sw::redis::Redis& redis) : AbstractGraph(), redis_(redis) {}

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
  sw::redis::Redis& redis_;

  std::vector<std::string> getAllKeys(const std::string& pattern) const;

  std::vector<graph::Node> getNodesByKeys(const std::vector<std::string>& keys) const;

  std::vector<graph::Edge> getEdgesByKeys(const std::vector<std::string>& keys) const;

  static std::string makeNodeKey(NodeId id);

  static std::string makeEdgeKey(EdgeId id);

  static std::pair<std::string, std::string> makeEdgePattern(NodeId id);

  static NodeId parseNodeKey(const std::string& key);

  static EdgeId parseEdgeKey(const std::string& key);
};
