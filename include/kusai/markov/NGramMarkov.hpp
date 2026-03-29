#pragma once

#include "SimpleMarkov.hpp"
#include "absl/log/check.h"

namespace kusai {
class NGramMarkov : public SimpleMarkov {
 public:
  explicit NGramMarkov(const std::shared_ptr<AbstractGraph>& graph, const uint32_t contextSize = 1)
      : SimpleMarkov(graph), contextSize_(contextSize) {
    CHECK(contextSize_ > 0) << "Context size must be greater than 0.";
  }

  [[nodiscard]] nlohmann::json serialize() const override;
  bool deserialize(const nlohmann::json& data) override;

 protected:
  void trainUnlocked(const std::vector<std::vector<NodeId> >& sequences) override;

  [[nodiscard]] std::optional<NodeId> nextNodeUnlocked(const std::vector<NodeId>& context) const override;

 private:
  std::uint32_t contextSize_;

  static NodeId makeContextId(const std::vector<NodeId>& ids);
};
}  // namespace kusai
