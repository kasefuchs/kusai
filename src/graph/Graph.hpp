#pragma once

#include <graph.pb.h>

class Graph {
public:
  Graph() = default;

  virtual ~Graph() = default;

  absl::flat_hash_map<uint64_t, std::unique_ptr<graph::Node>> nodes;

  absl::flat_hash_map<absl::uint128, std::unique_ptr<graph::Edge>> edges;

  graph::Node *addNode(uint64_t id);

  [[nodiscard]] graph::Node *getNode(uint64_t id) const;

  graph::Node *getNode(const google::protobuf::Any &msg);

  graph::Node *getNode(const google::protobuf::Message &msg);

  graph::Node *getOrAddNode(uint64_t id);

  graph::Edge *addEdge(uint64_t source, uint64_t target);

  graph::Edge *addEdge(const graph::Node &source, const graph::Node &target);

  [[nodiscard]] graph::Edge *getEdge(uint64_t source, uint64_t target) const;

  [[nodiscard]] graph::Edge *getEdge(const graph::Node &source, const graph::Node &target) const;

  graph::Edge *getEdge(const google::protobuf::Any &msg);

  graph::Edge *getEdge(const google::protobuf::Message &msg);

  graph::Edge *getOrAddEdge(uint64_t source, uint64_t target);

  graph::Edge *getOrAddEdge(const graph::Node &source, const graph::Node &target);

  [[nodiscard]] std::vector<graph::Edge *> getOutgoingEdges(const graph::Node &source) const;

  void resetEdgeWeights();

  void serialize(graph::Graph &out) const;

  void deserialize(const graph::Graph &in);

  [[nodiscard]] std::string toGEXF() const;
};
