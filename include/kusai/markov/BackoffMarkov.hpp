#pragma once

#include <absl/log/check.h>

#include "AbstractMarkov.hpp"
#include "NGramMarkov.hpp"

namespace kusai {
class BackoffMarkov : public AbstractMarkov {
 public:
  explicit BackoffMarkov(const std::shared_ptr<AbstractGraph>& graph, const uint32_t maxContextSize = 1)
      : AbstractMarkov(graph), maxContextSize_(maxContextSize) {
    CHECK(maxContextSize_ > 0) << "Maximum context size must be greater than 0.";

    rebuildModels();
  }

  [[nodiscard]] nlohmann::json serialize() const override;
  bool deserialize(const nlohmann::json& data) override;

 protected:
  void trainUnlocked(const std::vector<std::vector<NodeId> >& sequences) override;

  [[nodiscard]] std::optional<NodeId> nextNodeUnlocked(const std::vector<NodeId>& context) const override;

 private:
  uint32_t maxContextSize_;
  std::vector<std::unique_ptr<NGramMarkov> > models_;

  void rebuildModels();
};
}  // namespace kusai
