#include "kusai/serializable/AbstractSerializable.hpp"

#include <istream>
#include <ostream>

namespace kusai {
void AbstractSerializable::serializeToOstream(std::ostream& out) const { out << serialize().dump(); }

void AbstractSerializable::deserializeFromIstream(std::istream& in) {
  nlohmann::json root;
  in >> root;
  deserialize(root);
}
}  // namespace kusai
