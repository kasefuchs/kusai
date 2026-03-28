#pragma once

#include <cstdint>

#include "kusai/serializable/AbstractSerializable.hpp"

namespace kusai {
using NodeId = std::uint64_t;

struct Node final : AbstractSerializable {
  NodeId id{};

  [[nodiscard]] nlohmann::json serialize() const override;
  void deserialize(const nlohmann::json& data) override;
};
}  // namespace kusai
