#pragma once

#include <string>
#include <pugixml.hpp>
#include <google/protobuf/util/json_util.h>

#include "graph.pb.h"

namespace graph {
  inline uint64_t makeEdgeId(const uint32_t source, const uint32_t target) {
    return static_cast<uint64_t>(source) << 32 | static_cast<uint64_t>(target);
  }

  inline std::string toD2(const Node &node) {
    std::string json;
    if (const auto status = google::protobuf::json::MessageToJsonString(node, &json); !status.ok()) {
      throw std::runtime_error("Failed to serialize node");
    }

    std::ostringstream oss;
    oss << node.id() << ": |json " << json << " |";
    return oss.str();
  }

  inline std::string toD2(const Edge &edge) {
    std::string json;
    if (const auto status = google::protobuf::json::MessageToJsonString(edge, &json); !status.ok()) {
      throw std::runtime_error("Failed to serialize edge metadata");
    }

    std::ostringstream oss;
    oss << edge.source() << " -> " << edge.target() << ": |json " << json << " |";
    return oss.str();
  }

  inline pugi::xml_node toGEXF(pugi::xml_node &parent, const Node &node) {
    std::string json;
    if (const auto status = google::protobuf::json::MessageToJsonString(node, &json); !status.ok()) {
      throw std::runtime_error("Failed to serialize node to JSON");
    }

    pugi::xml_node nodeElem = parent.append_child("node");
    nodeElem.append_attribute("id") = std::to_string(node.id()).c_str();

    pugi::xml_node attvalues = nodeElem.append_child("attvalues");
    pugi::xml_node attvalue = attvalues.append_child("attvalue");
    attvalue.append_attribute("for") = "node_json";
    attvalue.append_attribute("value") = json.c_str();

    return nodeElem;
  }

  inline pugi::xml_node toGEXF(pugi::xml_node &parent, const Edge &edge) {
    std::string json;
    if (const auto status = google::protobuf::json::MessageToJsonString(edge, &json); !status.ok()) {
      throw std::runtime_error("Failed to serialize edge to JSON");
    }

    const uint64_t eid = makeEdgeId(edge.source(), edge.target());

    pugi::xml_node edgeElem = parent.append_child("edge");
    edgeElem.append_attribute("id") = std::to_string(eid).c_str();
    edgeElem.append_attribute("source") = std::to_string(edge.source()).c_str();
    edgeElem.append_attribute("target") = std::to_string(edge.target()).c_str();
    edgeElem.append_attribute("weight") = std::to_string(edge.weight()).c_str();

    pugi::xml_node attvalues = edgeElem.append_child("attvalues");
    pugi::xml_node attvalue = attvalues.append_child("attvalue");
    attvalue.append_attribute("for") = "edge_json";
    attvalue.append_attribute("value") = json.c_str();

    return edgeElem;
  }
}
