#pragma once

#include <google/protobuf/util/json_util.h>

#include <string>

#include "graph.pb.h"

namespace graph {
inline absl::uint128 makeEdgeId(const uint64_t source, const uint64_t target) {
  return absl::MakeUint128(source, target);
}

inline std::string toJsonOrThrow(const google::protobuf::Message &msg, const std::string &err) {
  std::string json;
  if (const auto status = google::protobuf::json::MessageToJsonString(msg, &json); !status.ok()) {
    throw std::runtime_error(err);
  }

  return json;
}

inline pugi::xml_node toGEXF(pugi::xml_node &parent, const Node &node) {
  pugi::xml_node elem = parent.append_child("node");
  elem.append_attribute("id") = node.id();

  pugi::xml_node attValues = elem.append_child("attvalues");

  if (node.has_metadata() && !node.metadata().type_url().empty()) {
    const auto &type = node.metadata().type_url();
    pugi::xml_node typeAtt = attValues.append_child("attvalue");
    typeAtt.append_attribute("for") = "node_metadata_type";
    typeAtt.append_attribute("value") = type;
  }

  const auto json = toJsonOrThrow(node, "Failed to serialize node");
  pugi::xml_node jsonAtt = attValues.append_child("attvalue");
  jsonAtt.append_attribute("for") = "node_json";
  jsonAtt.append_attribute("value") = json;

  return elem;
}

inline pugi::xml_node toGEXF(pugi::xml_node &parent, const Edge &edge) {
  const absl::uint128 eid = makeEdgeId(edge.source(), edge.target());

  pugi::xml_node elem = parent.append_child("edge");
  elem.append_attribute("id") = absl::StrCat(eid);
  elem.append_attribute("source") = edge.source();
  elem.append_attribute("target") = edge.target();
  elem.append_attribute("weight") = edge.weight();

  pugi::xml_node attValues = elem.append_child("attvalues");

  if (edge.has_metadata() && !edge.metadata().type_url().empty()) {
    const auto &type = edge.metadata().type_url();
    pugi::xml_node typeAtt = attValues.append_child("attvalue");
    typeAtt.append_attribute("for") = "edge_metadata_type";
    typeAtt.append_attribute("value") = type;
  }

  const auto json = toJsonOrThrow(edge, "Failed to serialize edge");
  pugi::xml_node jsonAtt = attValues.append_child("attvalue");
  jsonAtt.append_attribute("for") = "edge_json";
  jsonAtt.append_attribute("value") = json;

  return elem;
}
} // namespace graph
