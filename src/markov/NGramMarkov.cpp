#include "NGramMarkov.hpp"

#include <xxhash.h>

#include <span>

void NGramMarkov::train(const std::vector<std::vector<graph::Node *>> &sequences) {
  const size_t windowSize = contextSize_ + 1;
  for (const auto &seq : sequences) {
    if (seq.size() < windowSize)
      continue;

    for (size_t i = 0; i + windowSize <= seq.size(); ++i) {
      std::span window(seq.data() + i, windowSize);

      std::vector<uint64_t> ctx;
      ctx.reserve(contextSize_);
      for (const auto *node : window.first(contextSize_))
        ctx.push_back(node->id());

      const auto id = makeContextId(ctx);
      auto *node = graph.getOrAddNode(id);

      auto metadata = markov::NGramNodeMetadata();
      metadata.mutable_context()->Assign(ctx.begin(), ctx.end());
      node->mutable_metadata()->PackFrom(metadata);

      const auto *next = window.back();
      auto *edge = graph.getOrAddEdge(*node, *next);
      edge->set_weight(edge->weight() + 1);
    }
  }
}

graph::Node *NGramMarkov::nextNode(const std::vector<graph::Node *> &context) const {
  if (context.size() < contextSize_)
    return nullptr;

  std::vector<uint64_t> ctx;
  ctx.reserve(contextSize_);
  for (const std::span window(context); const auto *node : window.last(contextSize_))
    ctx.push_back(node->id());

  const auto ctxId = makeContextId(ctx);
  if (const auto *it = graph.getNode(ctxId); it != nullptr)
    return Markov::nextNode(*it);

  return nullptr;
}

void NGramMarkov::serialize(google::protobuf::Any &out) const {
  markov::NGramMarkov container;

  container.set_context_size(contextSize_);
  graph.serialize(*container.mutable_graph());

  out.PackFrom(container);
}

void NGramMarkov::deserialize(const google::protobuf::Any &in) {
  markov::NGramMarkov container;
  in.UnpackTo(&container);

  contextSize_ = container.context_size();
  graph.deserialize(container.graph());
}

uint64_t NGramMarkov::makeContextId(const std::vector<uint64_t> &ids) {
  return XXH64(ids.data(), ids.size() * sizeof(uint64_t), 0);
}
