#include "kusai/markov/NGramMarkov.hpp"

#include <xxhash.h>

#include <cstddef>
#include <cstdint>
#include <optional>
#include <span>
#include <string>
#include <vector>

#include "kusai/graph/AbstractGraph.hpp"
#include "kusai/graph/Edge.hpp"
#include "kusai/graph/Node.hpp"
#include "kusai/markov/Markov.hpp"

void NGramMarkov::train(const std::vector<std::vector<NodeId> >& sequences) {
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

      graph.ensureNode(id);
      graph.modifyEdge(graph.ensureEdge(id, window.back()), [](Edge& edge) { edge.weight++; });
    }
  }
}

std::optional<NodeId> NGramMarkov::nextNode(const std::vector<NodeId>& context) const {
  if (context.size() < contextSize_) return std::nullopt;

  std::vector<uint64_t> ctx;
  ctx.reserve(contextSize_);
  for (const std::span window(context); const auto node : window.last(contextSize_)) {
    ctx.push_back(node);
  }

  const auto ctxId = makeContextId(ctx);
  return Markov::nextNode(ctxId);
}

void NGramMarkov::serialize(pugi::xml_node& self) const {
  graph.serializeToParent(self);

  self.append_attribute("context_size").set_value(contextSize_);
}

void NGramMarkov::deserialize(const pugi::xml_node& self) {
  graph.deserializeFromParent(self);

  contextSize_ = self.attribute("context_size").as_uint();
}

std::string NGramMarkov::tagName() const { return "NGramMarkov"; }

NodeId NGramMarkov::makeContextId(const std::vector<NodeId>& ids) {
  return XXH64(ids.data(), ids.size() * sizeof(NodeId), 0);
}
