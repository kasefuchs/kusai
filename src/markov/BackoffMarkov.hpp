#pragma once

#include <absl/log/check.h>

#include "AbstractMarkov.hpp"
#include "NGramMarkov.hpp"

class BackoffMarkov : public AbstractMarkov {
 public:
  explicit BackoffMarkov(AbstractGraph& graph, const uint32_t maxContextSize = 1)
      : AbstractMarkov(graph), maxContextSize_(maxContextSize) {
    CHECK(maxContextSize_ > 0) << "Maximum context size must be greater than 0.";

    rebuildModels();
  }

  void train(const std::vector<std::vector<NodeId>>& sequences) override;

  [[nodiscard]] std::optional<NodeId> nextNode(const std::vector<NodeId>& context) const override;

  void serialize(google::protobuf::Any& out) const override;

  void deserialize(const google::protobuf::Any& in) override;

 private:
  uint32_t maxContextSize_;
  std::vector<std::unique_ptr<NGramMarkov>> models_;

  void rebuildModels();
};
