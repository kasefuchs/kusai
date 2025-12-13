#include <span>

#include "NGramMarkov.hpp"

void NGramMarkov::train(const std::vector<std::vector<graph::Node *> > &sequences) {
  Markov::train({});

  for (const auto &seq: sequences) {
    if (seq.size() < n_) continue;

    for (size_t i = 0; i + n_ <= seq.size(); ++i) {
      std::span window(seq.data() + i, n_);

      std::vector<uint32_t> ctx;
      for (const auto *node: window.first(n_ - 1)) ctx.push_back(node->id());

      const auto id = makeContextId(ctx);
      const auto *node = getOrAddNode(id);
      const auto *next = window.back();

      auto *edge = getOrAddEdge(*node, *next);
      edge->set_weight(edge->weight() + 1);
    }
  }
}

graph::Node *NGramMarkov::nextNode(const std::vector<graph::Node *> &context) const {
  const std::span window(context);

  std::vector<uint32_t> ctx;
  for (const auto *node: window.last(n_ - 1)) ctx.push_back(node->id());

  const auto ctxId = makeContextId(ctx);
  const auto *it = getNode(ctxId);

  return Markov::nextNode(*it);
}

void NGramMarkov::serialize(markov::NGramMarkov &out) const {
  out.set_n(n_);
  Graph::serialize(*out.mutable_graph());
}

void NGramMarkov::deserialize(const markov::NGramMarkov &in) {
  n_ = in.n();
  Graph::deserialize(in.graph());
}

uint32_t NGramMarkov::makeContextId(const std::vector<uint32_t> &ids) {
  uint32_t hash = 0x811c9dc5;
  for (const uint32_t id: ids) {
    hash ^= id;
    hash *= 0x01000193;
  }

  return hash;
}
