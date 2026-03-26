#pragma once

#include "Node.hpp"
#include "kusai/common/AbstractSerializable.hpp"

namespace kusai {
using EdgeId = std::uint64_t;

struct Edge final : AbstractSerializable {
  NodeId source{};
  NodeId target{};
  std::uint32_t weight{};

  void serialize(pugi::xml_node& self) const override;

  void deserialize(const pugi::xml_node& self) override;

  [[nodiscard]] std::string tagName() const override;

  static EdgeId makeId(NodeId source, NodeId target);
};
}  // namespace kusai
