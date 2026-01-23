#pragma once

#include "Markov.hpp"
#include "markov.pb.h"

#include "absl/log/check.h"

class NGramMarkov : public Markov {
public:
  explicit NGramMarkov(AbstractGraph &graph, const uint32_t contextSize = 1)
      : Markov(graph), contextSize_(contextSize) {
    CHECK(contextSize_ > 0) << "Context size must be greater than 0.";
  }

  void train(const std::vector<std::vector<NodeId>> &sequences) override;

  std::optional<NodeId> nextNode(const std::vector<NodeId> &context) const override;

  void serialize(google::protobuf::Any &out) const override;

  void deserialize(const google::protobuf::Any &in) override;

private:
  uint32_t contextSize_;

  static NodeId makeContextId(const std::vector<NodeId> &ids);
};
