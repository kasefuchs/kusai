// Copyright (c) Kasefuchs
// SPDX-License-Identifier: MIT

#pragma once

#include <string>
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
    if (const auto status = google::protobuf::json::MessageToJsonString(edge.metadata(), &json); !status.ok()) {
      throw std::runtime_error("Failed to serialize edge metadata");
    }

    std::ostringstream oss;
    oss << edge.source() << " -> " << edge.target() << ": |json " << json << " |";
    return oss.str();
  }
}
