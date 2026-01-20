#pragma once

#include "Markov.hpp"
#include "markov.pb.h"

class NGramMarkov : public Markov {
public:
  explicit NGramMarkov(Graph &graph, const uint32_t contextSize = 1) : Markov(graph), contextSize_(contextSize) {
    assert(contextSize_ > 0);
  }

  void train(const std::vector<std::vector<graph::Node *>> &sequences) override;

  graph::Node *nextNode(const std::vector<graph::Node *> &context) const override;

  void serialize(google::protobuf::Any &out) const override;

  void deserialize(const google::protobuf::Any &in) override;

private:
  uint32_t contextSize_;

  static uint64_t makeContextId(const std::vector<uint64_t> &ids);
};
