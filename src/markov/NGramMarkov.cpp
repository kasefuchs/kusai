#include "NGramMarkov.hpp"

#include <xxhash.h>

#include <span>

void NGramMarkov::train(const std::vector<std::vector<NodeId>> &sequences) {
  const size_t windowSize = contextSize_ + 1;
  for (const auto &seq : sequences) {
    if (seq.size() < windowSize) {
      continue;
    }

    for (size_t i = 0; i + windowSize <= seq.size(); ++i) {
      std::span window(seq.data() + i, windowSize);

      std::vector<uint64_t> ctx;
      ctx.reserve(contextSize_);
      for (const auto node : window.first(contextSize_)) {
        ctx.push_back(node);
      }

      const auto id = makeContextId(ctx);

      graph.modifyNode(graph.ensureNode(id), [&](graph::Node &node) {
        auto metadata = markov::NGramNodeMetadata();
        metadata.mutable_context()->Assign(ctx.begin(), ctx.end());
        node.mutable_metadata()->PackFrom(metadata);
      });

      graph.modifyEdge(graph.ensureEdge(id, window.back()),
                       [](graph::Edge &edge) { edge.set_weight(edge.weight() + 1); });
    }
  }
}

std::optional<NodeId> NGramMarkov::nextNode(const std::vector<NodeId> &context) const {
  if (context.size() < contextSize_) {
    return std::nullopt;
  }

  std::vector<uint64_t> ctx;
  ctx.reserve(contextSize_);
  for (const std::span window(context); const auto node : window.last(contextSize_)) {
    ctx.push_back(node);
  }

  const auto ctxId = makeContextId(ctx);
  return Markov::nextNode(ctxId);
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

NodeId NGramMarkov::makeContextId(const std::vector<NodeId> &ids) {
  return XXH64(ids.data(), ids.size() * sizeof(NodeId), 0);
}
