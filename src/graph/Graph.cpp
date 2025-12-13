#include <google/protobuf/util/message_differencer.h>

#include "Graph.hpp"
#include "graph.hpp"

graph::Node *Graph::addNode(const uint32_t id) {
  auto node = std::make_unique<graph::Node>();
  node->set_id(id);

  auto [it, _] = nodes_.emplace(node->id(), std::move(node));
  return it->second.get();
}

graph::Node *Graph::addNode() {
  return addNode(idGenerator.next());
}

graph::Node *Graph::getNode(const uint32_t id) const {
  if (const auto it = nodes_.find(id); it != nodes_.end()) return it->second.get();
  return nullptr;
}

graph::Node *Graph::getNode(const google::protobuf::Any &msg) {
  for (const auto &node: nodes_ | std::views::values) {
    if (google::protobuf::util::MessageDifferencer::Equals(node->metadata(), msg)) {
      return node.get();
    }
  }

  return nullptr;
}

graph::Node *Graph::getNode(const google::protobuf::Message &msg) {
  google::protobuf::Any anyMsg;
  anyMsg.PackFrom(msg);

  return getNode(anyMsg);
}

graph::Node *Graph::getOrAddNode(const uint32_t id) {
  if (auto *node = getNode(id)) return node;
  return addNode(id);
}

graph::Edge *Graph::addEdge(const uint32_t source, const uint32_t target) {
  const uint64_t id = graph::makeEdgeId(source, target);

  auto edge = std::make_unique<graph::Edge>();
  edge->set_source(source);
  edge->set_target(target);

  const auto [it, _] = edges_.emplace(id, std::move(edge));
  return it->second.get();
}

graph::Edge *Graph::addEdge(const graph::Node &source, const graph::Node &target) {
  return addEdge(source.id(), target.id());
}

graph::Edge *Graph::getEdge(const uint32_t source, const uint32_t target) const {
  const uint64_t id = graph::makeEdgeId(source, target);
  if (const auto it = edges_.find(id); it != edges_.end()) return it->second.get();
  return nullptr;
}

graph::Edge *Graph::getEdge(const graph::Node &source, const graph::Node &target) const {
  return getEdge(source.id(), target.id());
}

graph::Edge *Graph::getEdge(const google::protobuf::Any &msg) {
  for (const auto &edge: edges_ | std::views::values) {
    if (google::protobuf::util::MessageDifferencer::Equals(edge->metadata(), msg)) {
      return edge.get();
    }
  }

  return nullptr;
}

graph::Edge *Graph::getEdge(const google::protobuf::Message &msg) {
  google::protobuf::Any anyMsg;
  anyMsg.PackFrom(msg);

  return getEdge(anyMsg);
}

std::vector<graph::Edge *> Graph::getOutgoingEdges(const graph::Node &source) const {
  std::vector<graph::Edge *> result;
  for (const auto &edge: edges_ | std::views::values) {
    if (edge->source() == source.id()) result.emplace_back(edge.get());
  }

  return result;
}

graph::Edge *Graph::getOrAddEdge(const uint32_t source, const uint32_t target) {
  if (auto *edge = getEdge(source, target)) return edge;
  return addEdge(source, target);
}

graph::Edge *Graph::getOrAddEdge(const graph::Node &source, const graph::Node &target) {
  return getOrAddEdge(source.id(), target.id());
}

void Graph::serialize(graph::Graph &out) const {
  idGenerator.serialize(*out.mutable_id_generator());

  for (const auto &node: nodes_ | std::views::values) out.add_nodes()->CopyFrom(*node);
  for (const auto &edge: edges_ | std::views::values) out.add_edges()->CopyFrom(*edge);
}

void Graph::deserialize(const graph::Graph &in) {
  idGenerator.deserialize(in.id_generator());

  nodes_.clear();
  edges_.clear();

  for (const auto &nodeProto: in.nodes()) addNode(nodeProto.id())->CopyFrom(nodeProto);
  for (const auto &edgeProto: in.edges()) addEdge(edgeProto.source(), edgeProto.target());
}

std::string Graph::toD2() const {
  std::ostringstream buf;

  for (const auto &node: nodes_ | std::views::values) buf << graph::toD2(*node) << std::endl;
  for (const auto &edge: edges_ | std::views::values) buf << graph::toD2(*edge) << std::endl;

  return buf.str();
}
