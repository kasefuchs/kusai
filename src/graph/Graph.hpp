#pragma once

#include <graph.pb.h>

#include "IdGenerator.hpp"

class Graph {
public:
  Graph() = default;

  ~Graph() = default;

  graph::Node *addNode(uint32_t id);

  graph::Node *addNode();

  graph::Node *getNode(uint32_t id) const;

  graph::Node *getOrAddNode(uint32_t id);

  graph::Edge *addEdge(uint32_t source, uint32_t target);

  graph::Edge *addEdge(const graph::Node &source, const graph::Node &target);

  graph::Edge *getEdge(uint32_t source, uint32_t target) const;

  graph::Edge *getEdge(const graph::Node &source, const graph::Node &target) const;

  graph::Edge *getOrAddEdge(uint32_t source, uint32_t target);

  graph::Edge *getOrAddEdge(const graph::Node &source, const graph::Node &target);

  std::vector<graph::Edge *> getOutgoingEdges(const graph::Node &source) const;

  void serialize(graph::Graph &out) const;

  void deserialize(const graph::Graph &in);

  [[nodiscard]] std::string toD2() const;

protected:
  IdGenerator idGenerator;

  std::unordered_map<uint32_t, std::unique_ptr<graph::Node> > nodes_;
  std::unordered_map<uint64_t, std::unique_ptr<graph::Edge> > edges_;
};
