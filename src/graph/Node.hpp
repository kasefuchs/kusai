// Copyright (c) Kasefuchs
// SPDX-License-Identifier: MIT

#pragma once

#include "graph.pb.h"

class Node {
public:
    explicit Node(uint32_t id);

    ~Node() = default;

    [[nodiscard]] uint32_t id() const;

    void serialize(graph::Node* out) const;

    void deserialize(const graph::Node* in);

private:
    uint32_t id_;
};
