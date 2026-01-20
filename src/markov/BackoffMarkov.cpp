#include "BackoffMarkov.hpp"

void BackoffMarkov::train(const std::vector<std::vector<graph::Node *>> &sequences) {
  for (const auto &model : models_ | std::views::values) {
    model->train(sequences);
  }
}

graph::Node *BackoffMarkov::nextNode(const std::vector<graph::Node *> &context) const {
  for (uint32_t n = maxContextSize_; n > 0; --n) {
    if (auto it = models_.find(n); it != models_.end()) {
      if (graph::Node *node = it->second->nextNode(context); node != nullptr)
        return node;
    }
  }

  return nullptr;
}

void BackoffMarkov::serialize(google::protobuf::Any &out) const {
  markov::BackoffMarkov container;

  container.set_max_context_size(maxContextSize_);
  graph.serialize(*container.mutable_graph());

  out.PackFrom(container);
}

void BackoffMarkov::deserialize(const google::protobuf::Any &in) {
  markov::BackoffMarkov container;
  in.UnpackTo(&container);

  maxContextSize_ = container.max_context_size();
  graph.deserialize(container.graph());

  rebuildModels();
}

void BackoffMarkov::rebuildModels() {
  models_.clear();
  for (uint32_t n = 1; n <= maxContextSize_; ++n) {
    models_.emplace(n, std::make_unique<NGramMarkov>(graph, n));
  }
}
