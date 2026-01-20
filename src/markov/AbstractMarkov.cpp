#include "AbstractMarkov.hpp"

#include <fstream>

void AbstractMarkov::serializeToOstream(std::ostream &out) const {
  google::protobuf::Any container;
  serialize(container);

  container.SerializeToOstream(&out);
}

void AbstractMarkov::deserializeFromIstream(std::istream &in) {
  google::protobuf::Any container;
  container.ParseFromIstream(&in);

  deserialize(container);
}
