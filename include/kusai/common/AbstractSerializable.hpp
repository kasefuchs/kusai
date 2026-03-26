#pragma once

#include <cstdint>
#include <string>

#include "pugixml.hpp"

namespace kusai {
class AbstractSerializable {
 public:
  virtual ~AbstractSerializable() = default;

  virtual void serialize(pugi::xml_node& self) const = 0;

  virtual void deserialize(const pugi::xml_node& self) = 0;

  void serializeToParent(pugi::xml_node& parent) const;

  void deserializeFromParent(const pugi::xml_node& parent);

  void serializeToOstream(std::ostream& out,
                          std::uint32_t format = pugi::format_raw | pugi::format_no_declaration) const;

  void deserializeFromIstream(std::istream& in);

 protected:
  explicit AbstractSerializable() = default;

  [[nodiscard]] virtual std::string tagName() const = 0;
};
}  // namespace kusai
