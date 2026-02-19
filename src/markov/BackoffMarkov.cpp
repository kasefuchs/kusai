#include "kusai/markov/BackoffMarkov.hpp"

#include <google/protobuf/any.pb.h>

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <memory>
#include <optional>
#include <ranges>
#include <vector>

#include "kusai/graph/AbstractGraph.hpp"
#include "kusai/proto/markov.pb.h"

void BackoffMarkov::train(const std::vector<std::vector<NodeId>>& sequences) {
  std::vector<std::vector<NodeId>> filtered;
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

void BackoffMarkov::serialize(google::protobuf::Any& out) const {
  markov::BackoffMarkov container;

  container.set_max_context_size(maxContextSize_);
  graph.serialize(*container.mutable_graph());

  out.PackFrom(container);
}

void BackoffMarkov::deserialize(const google::protobuf::Any& in) {
  markov::BackoffMarkov container;
  in.UnpackTo(&container);

  maxContextSize_ = container.max_context_size();
  graph.deserialize(container.graph());

  rebuildModels();
}

void BackoffMarkov::rebuildModels() {
  models_.clear();
  models_.reserve(maxContextSize_);

  for (uint32_t n = 1; n <= maxContextSize_; ++n) {
    models_.push_back(std::make_unique<NGramMarkov>(graph, n));
  }
}
