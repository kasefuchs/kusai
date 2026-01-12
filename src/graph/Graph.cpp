#include <fstream>
#include <pugixml.hpp>
#include <google/protobuf/util/message_differencer.h>

#include "Graph.hpp"
#include "helpers/graph.hpp"

graph::Node *Graph::addNode(const uint64_t id) {
  auto node = std::make_unique<graph::Node>();
  node->set_id(id);

  auto [it, _] = nodes_.emplace(node->id(), std::move(node));
  return it->second.get();
}

graph::Node *Graph::getNode(const uint64_t id) const {
  if (const auto it = nodes_.find(id); it != nodes_.end()) return it->second.get();
  return nullptr;
}

graph::Node *Graph::getNode(const google::protobuf::Any &msg) {
  for (const auto &node: nodes_ | std::views::values) {
    if (google::protobuf::util::MessageDifferencer::Equals(node->metadata(), msg)) return node.get();
  }

  return nullptr;
}

graph::Node *Graph::getNode(const google::protobuf::Message &msg) {
  google::protobuf::Any anyMsg;
  anyMsg.PackFrom(msg);

  return getNode(anyMsg);
}

graph::Node *Graph::getOrAddNode(const uint64_t id) {
  if (auto *node = getNode(id)) return node;
  return addNode(id);
}

graph::Edge *Graph::addEdge(const uint64_t source, const uint64_t target) {
  const absl::uint128 id = graph::makeEdgeId(source, target);

  auto edge = std::make_unique<graph::Edge>();
  edge->set_source(source);
  edge->set_target(target);

  const auto [it, _] = edges_.emplace(id, std::move(edge));
  return it->second.get();
}

graph::Edge *Graph::addEdge(const graph::Node &source, const graph::Node &target) {
  return addEdge(source.id(), target.id());
}

graph::Edge *Graph::getEdge(const uint64_t source, const uint64_t target) const {
  const absl::uint128 id = graph::makeEdgeId(source, target);
  if (const auto it = edges_.find(id); it != edges_.end()) return it->second.get();
  return nullptr;
}

graph::Edge *Graph::getEdge(const graph::Node &source, const graph::Node &target) const {
  return getEdge(source.id(), target.id());
}

graph::Edge *Graph::getEdge(const google::protobuf::Any &msg) {
  for (const auto &edge: edges_ | std::views::values) {
    if (google::protobuf::util::MessageDifferencer::Equals(edge->metadata(), msg)) return edge.get();
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

graph::Edge *Graph::getOrAddEdge(const uint64_t source, const uint64_t target) {
  if (auto *edge = getEdge(source, target)) return edge;
  return addEdge(source, target);
}

graph::Edge *Graph::getOrAddEdge(const graph::Node &source, const graph::Node &target) {
  return getOrAddEdge(source.id(), target.id());
}

void Graph::serialize(graph::Graph &out) const {
  for (const auto &node: nodes_ | std::views::values) out.add_nodes()->CopyFrom(*node);
  for (const auto &edge: edges_ | std::views::values) out.add_edges()->CopyFrom(*edge);
}

void Graph::serializeToOstream(std::ostream &out) const {
  graph::Graph model;
  serialize(model);

  model.SerializeToOstream(&out);
}

void Graph::serializeToFile(const std::string &filename) const {
  std::ofstream ofs(filename, std::ios::binary);

  serializeToOstream(ofs);
}

void Graph::deserialize(const graph::Graph &in) {
  nodes_.clear();
  edges_.clear();

  for (const auto &nodeProto: in.nodes()) addNode(nodeProto.id())->CopyFrom(nodeProto);
  for (const auto &edgeProto: in.edges()) addEdge(edgeProto.source(), edgeProto.target())->CopyFrom(edgeProto);
}

void Graph::deserializeFromIstream(std::istream &in) {
  graph::Graph model;
  model.ParseFromIstream(&in);

  deserialize(model);
}

void Graph::deserializeFromFile(const std::string &filename) {
  std::ifstream ifs(filename, std::ios::binary);

  deserializeFromIstream(ifs);
}

std::string Graph::toGEXF() const {
  pugi::xml_document doc;

  pugi::xml_node gexf = doc.append_child("gexf");
  gexf.append_attribute("xmlns") = "https://gexf.net/1.2";
  gexf.append_attribute("version") = "1.2";

  pugi::xml_node graphNode = gexf.append_child("graph");
  graphNode.append_attribute("mode") = "static";
  graphNode.append_attribute("defaultedgetype") = "directed";

  pugi::xml_node nodeAttrs = graphNode.append_child("attributes");
  nodeAttrs.append_attribute("class") = "node";
  nodeAttrs.append_attribute("mode") = "static";

  pugi::xml_node nodeTypeAttr = nodeAttrs.append_child("attribute");
  nodeTypeAttr.append_attribute("id") = "node_metadata_type";
  nodeTypeAttr.append_attribute("type") = "string";
  nodeTypeAttr.append_attribute("title") = "type";

  pugi::xml_node nodeJsonAttr = nodeAttrs.append_child("attribute");
  nodeJsonAttr.append_attribute("id") = "node_json";
  nodeJsonAttr.append_attribute("type") = "string";
  nodeJsonAttr.append_attribute("title") = "data";

  pugi::xml_node edgeAttrs = graphNode.append_child("attributes");
  edgeAttrs.append_attribute("class") = "edge";
  edgeAttrs.append_attribute("mode") = "static";

  pugi::xml_node edgeTypeAttr = edgeAttrs.append_child("attribute");
  edgeTypeAttr.append_attribute("id") = "edge_metadata_type";
  edgeTypeAttr.append_attribute("type") = "string";
  edgeTypeAttr.append_attribute("title") = "type";

  pugi::xml_node edgeJsonAttr = edgeAttrs.append_child("attribute");
  edgeJsonAttr.append_attribute("id") = "edge_json";
  edgeJsonAttr.append_attribute("type") = "string";
  edgeJsonAttr.append_attribute("title") = "data";

  pugi::xml_node nodesNode = graphNode.append_child("nodes");
  for (const auto &node: nodes_ | std::views::values) graph::toGEXF(nodesNode, *node);

  pugi::xml_node edgesNode = graphNode.append_child("edges");
  for (const auto &edge: edges_ | std::views::values) graph::toGEXF(edgesNode, *edge);

  std::ostringstream oss;
  doc.save(oss);
  return oss.str();
}
