#pragma once

#include <absl/numeric/int128.h>

#include "Node.hpp"
#include "kusai/common/Serializable.hpp"

namespace kusai {
using EdgeId = absl::uint128;

struct Edge final : Serializable {
  NodeId source{};
  NodeId target{};
  std::uint32_t weight{};

  void serialize(pugi::xml_node& self) const override;

  void deserialize(const pugi::xml_node& self) override;

  [[nodiscard]] std::string tagName() const override;

  static EdgeId makeId(NodeId source, NodeId target);

  static std::pair<NodeId, NodeId> splitId(EdgeId id);
};
}  // namespace kusai
