#pragma once

#include <graph.pb.h>

class Graph {
public:
  Graph() = default;

  virtual ~Graph() = default;

  graph::Node *addNode(uint64_t id);

  graph::Node *getNode(uint64_t id) const;

  graph::Node *getNode(const google::protobuf::Any &msg);

  graph::Node *getNode(const google::protobuf::Message &msg);

  graph::Node *getOrAddNode(uint64_t id);

  graph::Edge *addEdge(uint64_t source, uint64_t target);

  graph::Edge *addEdge(const graph::Node &source, const graph::Node &target);

  graph::Edge *getEdge(uint64_t source, uint64_t target) const;

  graph::Edge *getEdge(const graph::Node &source, const graph::Node &target) const;

  graph::Edge *getEdge(const google::protobuf::Any &msg);

  graph::Edge *getEdge(const google::protobuf::Message &msg);

  graph::Edge *getOrAddEdge(uint64_t source, uint64_t target);

  graph::Edge *getOrAddEdge(const graph::Node &source, const graph::Node &target);

  std::vector<graph::Edge *> getOutgoingEdges(const graph::Node &source) const;

  void serialize(graph::Graph &out) const;

  virtual void serializeToOstream(std::ostream &out) const;

  void serializeToFile(const std::string &filename) const;

  void deserialize(const graph::Graph &in);

  virtual void deserializeFromIstream(std::istream &in);

  void deserializeFromFile(const std::string &filename);

  [[nodiscard]] std::string toGEXF() const;

protected:
  absl::flat_hash_map<uint64_t, std::unique_ptr<graph::Node> > nodes_;
  absl::flat_hash_map<absl::uint128, std::unique_ptr<graph::Edge> > edges_;
};
