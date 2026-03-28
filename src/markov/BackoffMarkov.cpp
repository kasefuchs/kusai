#include "kusai/markov/BackoffMarkov.hpp"

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <memory>
#include <mutex>
#include <optional>
#include <ranges>
#include <string>
#include <vector>

#include "kusai/graph/AbstractGraph.hpp"
#include "kusai/graph/Node.hpp"

namespace kusai {
nlohmann::json BackoffMarkov::serialize() const {
  std::shared_lock lock(mutex_);
  return {
      {"graph", graph->serialize()},
      {"max_context_size", maxContextSize_},
  };
}

void BackoffMarkov::deserialize(const nlohmann::json& data) {
  std::unique_lock lock(mutex_);
  data.at("max_context_size").get_to(maxContextSize_);

  graph->deserialize(data.at("graph"));
  rebuildModels();
}

void BackoffMarkov::trainUnlocked(const std::vector<std::vector<NodeId> >& sequences) {
  std::vector<std::vector<NodeId> > filtered;
  filtered.reserve(sequences.size());

  std::ranges::copy_if(sequences, std::back_inserter(filtered),
                       [this](const auto& seq) { return seq.size() >= maxContextSize_ + 1; });

  for (const auto& model : models_) model->train(filtered);
}

std::optional<NodeId> BackoffMarkov::nextNodeUnlocked(const std::vector<NodeId>& context) const {
  for (const auto& model : models_ | std::views::reverse) {
    if (auto node = model->nextNode(context); node.has_value()) {
      return node;
    }
  }

  return std::nullopt;
}

void BackoffMarkov::rebuildModels() {
  models_.clear();
  models_.reserve(maxContextSize_);

  for (uint32_t n = 1; n <= maxContextSize_; ++n) {
    models_.push_back(std::make_unique<NGramMarkov>(graph, n));
  }
}
}  // namespace kusai
