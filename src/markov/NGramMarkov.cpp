#include "kusai/markov/NGramMarkov.hpp"

#include <xxhash.h>

#include <cstddef>
#include <cstdint>
#include <mutex>
#include <optional>
#include <span>
#include <string>
#include <vector>

#include "kusai/graph/AbstractGraph.hpp"
#include "kusai/graph/Edge.hpp"
#include "kusai/graph/Node.hpp"
#include "kusai/markov/SimpleMarkov.hpp"

namespace kusai {
nlohmann::json NGramMarkov::serialize() const {
  std::shared_lock lock(mutex_);
  return {{"graph", graph->serialize()}, {"context_size", contextSize_}};
}

void NGramMarkov::deserialize(const nlohmann::json& data) {
  std::unique_lock lock(mutex_);
  data.at("context_size").get_to(contextSize_);

  graph->deserialize(data.at("graph"));
}

void NGramMarkov::trainUnlocked(const std::vector<std::vector<NodeId> >& sequences) {
  const size_t windowSize = contextSize_ + 1;
  for (const auto& seq : sequences) {
    if (seq.size() < windowSize) continue;

    for (size_t i = 0; i + windowSize <= seq.size(); ++i) {
      std::span window(seq.data() + i, windowSize);

      std::vector<uint64_t> ctx;
      ctx.reserve(contextSize_);
      for (const auto node : window.first(contextSize_)) {
        ctx.push_back(node);
      }

      const auto id = makeContextId(ctx);

      graph->ensureNode(id);
      graph->modifyEdge(graph->ensureEdge(id, window.back()), [](Edge& edge) { edge.weight++; });
    }
  }
}

std::optional<NodeId> NGramMarkov::nextNodeUnlocked(const std::vector<NodeId>& context) const {
  if (context.size() < contextSize_) return std::nullopt;

  std::vector<uint64_t> ctx;
  ctx.reserve(contextSize_);
  for (const std::span window(context); const auto node : window.last(contextSize_)) {
    ctx.push_back(node);
  }

  const auto ctxId = makeContextId(ctx);
  return SimpleMarkov::nextNodeUnlocked(ctxId);
}

NodeId NGramMarkov::makeContextId(const std::vector<NodeId>& ids) {
  return XXH64(ids.data(), ids.size() * sizeof(NodeId), 0);
}
}  // namespace kusai
