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

std::vector<graph::Node *> AbstractMarkov::generateNodes(const std::vector<graph::Node *> &context,
                                                         uint32_t limit = UINT32_MAX) const {
  std::vector<graph::Node *> result = context;

  while (limit--) {
    graph::Node *node = nextNode(result);
    if (!node)
      break;

    result.push_back(node);
  }

  return result;
}
