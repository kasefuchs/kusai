#include "kusai/common/AbstractSerializable.hpp"

#include <istream>
#include <ostream>

namespace kusai {
void AbstractSerializable::serializeToParent(pugi::xml_node& parent) const {
  auto node = parent.append_child(tagName().c_str());

  serialize(node);
}

void AbstractSerializable::deserializeFromParent(const pugi::xml_node& parent) {
  const auto node = parent.child(tagName().c_str());

  deserialize(node);
}

void AbstractSerializable::serializeToOstream(std::ostream& out, const std::uint32_t format) const {
  pugi::xml_document doc;
  serializeToParent(doc);
  doc.save(out, "\t", format);
}

void AbstractSerializable::deserializeFromIstream(std::istream& in) {
  pugi::xml_document doc;
  doc.load(in);

  deserializeFromParent(doc);
}
}  // namespace kusai
