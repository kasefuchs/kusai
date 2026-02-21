#pragma once

#include <string>

#include "pugixml.hpp"

class Serializable {
 public:
  virtual ~Serializable() = default;

  virtual void serialize(pugi::xml_node& self) const = 0;

  virtual void deserialize(const pugi::xml_node& self) = 0;

  void serializeToParent(pugi::xml_node& parent) const;

  void deserializeFromParent(const pugi::xml_node& parent);

  void serializeToOstream(std::ostream& out) const;

  void deserializeFromIstream(std::istream& in);

  [[nodiscard]] virtual std::string tagName() const = 0;

 protected:
  explicit Serializable() = default;
};
