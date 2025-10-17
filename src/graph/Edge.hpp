// Copyright (c) Kasefuchs
// SPDX-License-Identifier: MIT

#pragma once

#include "graph.pb.h"

class Edge {
public:
  explicit Edge(uint32_t sourceId, uint32_t targetId);

  ~Edge() = default;

  [[nodiscard]] uint32_t sourceId() const;
 [[nodiscard]] uint32_t targetId() const;

  void serialize(graph::Edge *out) const;

  void deserialize(const graph::Edge *in);

private:
  uint32_t sourceId_;
  uint32_t targetId_;
};
