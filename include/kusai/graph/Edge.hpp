#pragma once

#include "Node.hpp"
#include "kusai/serializable/AbstractSerializable.hpp"

namespace kusai {
using EdgeId = std::uint64_t;

struct Edge final : AbstractSerializable {
  NodeId source{};
  NodeId target{};
  std::uint32_t weight{};

  [[nodiscard]] nlohmann::json serialize() const override;
  void deserialize(const nlohmann::json& data) override;

  static EdgeId makeId(NodeId source, NodeId target);
};
}  // namespace kusai
