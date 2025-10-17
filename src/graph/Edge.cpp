// Copyright (c) Kasefuchs
// SPDX-License-Identifier: MIT

#include "Edge.hpp"

Edge::Edge(const uint32_t sourceId, const uint32_t targetId)
  : sourceId_(sourceId), targetId_(targetId) {
}

uint32_t Edge::sourceId() const {
  return sourceId_;
}

uint32_t Edge::targetId() const {
  return targetId_;
}

void Edge::serialize(graph::Edge *out) const {
  out->set_source(sourceId_);
  out->set_target(targetId_);
}

void Edge::deserialize(const graph::Edge *in) {
  sourceId_ = in->source();
  targetId_ = in->target();
}
