#pragma once

#include <cstdint>
#include <pugixml.hpp>

#include "kusai/common/Serializable.hpp"

using NodeId = std::uint64_t;

struct Node final : Serializable {
  NodeId id{};

  void serialize(pugi::xml_node& self) const override;

  void deserialize(const pugi::xml_node& self) override;

  [[nodiscard]] std::string tagName() const override;
};
