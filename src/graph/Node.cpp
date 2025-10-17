// Copyright (c) Kasefuchs
// SPDX-License-Identifier: MIT

#include "Node.hpp"

Node::Node(const uint32_t id) : id_(id) {
}

uint32_t Node::id() const {
  return id_;
}

void Node::serialize(graph::Node *out) const {
  out->set_id(id_);
}

void Node::deserialize(const graph::Node *in) {
  id_ = in->id();
}
