#pragma once
#define JSON_USE_IMPLICIT_CONVERSIONS 0

#include "nlohmann/json.hpp"

namespace kusai {
class AbstractSerializable {
 public:
  virtual ~AbstractSerializable() = default;

  [[nodiscard]] virtual nlohmann::json serialize() const = 0;

  virtual void deserialize(const nlohmann::json& data) = 0;

  void serializeToOstream(std::ostream& out) const;

  void deserializeFromIstream(std::istream& in);

 protected:
  explicit AbstractSerializable() = default;
};
}  // namespace kusai
