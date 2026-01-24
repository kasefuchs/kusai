#include "AbstractMarkov.hpp"

#include <google/protobuf/any.pb.h>

#include <cstdint>
#include <istream>
#include <ostream>
#include <vector>

#include "AbstractGraph.hpp"

void AbstractMarkov::serializeToOstream(std::ostream& out) const {
  google::protobuf::Any container;
  serialize(container);

  container.SerializeToOstream(&out);
}

void AbstractMarkov::deserializeFromIstream(std::istream& in) {
  google::protobuf::Any container;
  container.ParseFromIstream(&in);

  deserialize(container);
}

std::vector<NodeId> AbstractMarkov::generateNodes(const std::vector<NodeId>& context, uint32_t limit) const {
  std::vector<NodeId> result = context;

  while (limit--) {
    auto node = nextNode(result);
    if (!node.has_value()) {
      break;
    }

    result.push_back(*node);
  }

  return result;
}
