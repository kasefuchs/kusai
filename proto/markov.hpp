// Copyright (c) Kasefuchs
// SPDX-License-Identifier: MIT

#pragma once

#include "graph.pb.h"
#include "markov.pb.h"

namespace markov {
  inline bool unpackNodeMetadata(const graph::Node &node, NodeMetadata *meta) {
    return node.metadata().UnpackTo(meta);
  }

  inline bool packNodeMetadata(graph::Node &node, const NodeMetadata &meta) {
    return node.mutable_metadata()->PackFrom(meta);
  }

  inline bool unpackEdgeMetadata(const graph::Edge &edge, EdgeMetadata *meta) {
    return edge.metadata().UnpackTo(meta);
  }

  inline bool packEdgeMetadata(graph::Edge &edge, const EdgeMetadata &meta) {
    return edge.mutable_metadata()->PackFrom(meta);
  }

  inline bool resetEdgeMetadata(graph::Edge &edge) {
    static const EdgeMetadata resetMeta = [] {
      EdgeMetadata meta;
      meta.set_count(0);
      return meta;
    }();

    return packEdgeMetadata(edge, resetMeta);
  }
}
