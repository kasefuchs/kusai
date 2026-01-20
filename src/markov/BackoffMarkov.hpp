#pragma once

#include "AbstractMarkov.hpp"
#include "NGramMarkov.hpp"

class BackoffMarkov : public AbstractMarkov {
public:
  explicit BackoffMarkov(Graph &graph, const uint32_t maxContextSize = 1)
      : AbstractMarkov(graph), maxContextSize_(maxContextSize) {
    assert(maxContextSize_ > 0);
    rebuildModels();
  }

  void train(const std::vector<std::vector<graph::Node *>> &sequences) override;

  graph::Node *nextNode(const std::vector<graph::Node *> &context) const override;

  void serialize(google::protobuf::Any &out) const override;

  void deserialize(const google::protobuf::Any &in) override;

private:
  uint32_t maxContextSize_;
  absl::flat_hash_map<uint32_t, std::unique_ptr<NGramMarkov>> models_;

  void rebuildModels();
};
