#include "kusai/markov/BackoffMarkov.hpp"

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <memory>
#include <optional>
#include <ranges>
#include <string>
#include <vector>

#include "kusai/graph/AbstractGraph.hpp"
#include "kusai/graph/Node.hpp"

void BackoffMarkov::train(const std::vector<std::vector<NodeId> >& sequences) {
  std::vector<std::vector<NodeId> > filtered;
  filtered.reserve(sequences.size());

  std::ranges::copy_if(sequences, std::back_inserter(filtered),
                       [this](const auto& seq) { return seq.size() >= maxContextSize_ + 1; });

  for (const auto& model : models_) model->train(filtered);
}

std::optional<NodeId> BackoffMarkov::nextNode(const std::vector<NodeId>& context) const {
  for (const auto& model : models_ | std::views::reverse) {
    if (auto node = model->nextNode(context); node.has_value()) {
      return node;
    }
  }

  return std::nullopt;
}

void BackoffMarkov::serialize(pugi::xml_node& self) const {
  graph.serializeToParent(self);

  self.append_attribute("max_context_size") = maxContextSize_;
}

void BackoffMarkov::deserialize(const pugi::xml_node& self) {
  graph.deserializeFromParent(self);

  maxContextSize_ = self.attribute("max_context_size").as_uint();

  rebuildModels();
}

std::string BackoffMarkov::tagName() const { return "BackoffMarkov"; }

void BackoffMarkov::rebuildModels() {
  models_.clear();
  models_.reserve(maxContextSize_);

  for (uint32_t n = 1; n <= maxContextSize_; ++n) {
    models_.push_back(std::make_unique<NGramMarkov>(graph, n));
  }
}
