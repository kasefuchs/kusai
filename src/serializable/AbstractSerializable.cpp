#include "kusai/serializable/AbstractSerializable.hpp"

#include <iostream>
#include <istream>
#include <nlohmann/json.hpp>

namespace kusai {
void AbstractSerializable::serializeToOstream(std::ostream& out) const { out << serialize(); }

bool AbstractSerializable::deserializeFromIstream(std::istream& in) {
  try {
    nlohmann::json root;
    in >> root;
    return deserialize(root);
  } catch (const nlohmann::json::exception& e) {
  }

  return false;
}
}  // namespace kusai
