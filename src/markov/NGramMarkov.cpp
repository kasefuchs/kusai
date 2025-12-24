#include <span>
#include <xxhash.h>

#include "NGramMarkov.hpp"

void NGramMarkov::train(const std::vector<std::vector<graph::Node *> > &sequences) {
  Markov::train({});

  for (const auto &seq: sequences) {
    if (seq.size() < n_) continue;

    for (size_t i = 0; i + n_ <= seq.size(); ++i) {
      std::span window(seq.data() + i, n_);

      std::vector<uint64_t> ctx;
      for (const auto *node: window.first(n_ - 1)) ctx.push_back(node->id());

      const auto id = makeContextId(ctx);
      auto *node = getOrAddNode(id);

      auto metadata = markov::NGramNodeMetadata();
      metadata.mutable_context()->Assign(ctx.begin(), ctx.end());
      node->mutable_metadata()->PackFrom(metadata);

      const auto *next = window.back();
      auto *edge = getOrAddEdge(*node, *next);
      edge->set_weight(edge->weight() + 1);
    }
  }
}

graph::Node *NGramMarkov::nextNode(const std::vector<graph::Node *> &context) const {
  const std::span window(context);
  if (window.size() < n_ - 1) return nullptr;

  std::vector<uint64_t> ctx;
  for (const auto *node: window.last(n_ - 1)) ctx.push_back(node->id());

  const auto ctxId = makeContextId(ctx);
  if (const auto *it = getNode(ctxId); it != nullptr) return Markov::nextNode(*it);

  return nullptr;
}

void NGramMarkov::serialize(markov::NGramMarkov &out) const {
  out.set_n(n_);
  Graph::serialize(*out.mutable_graph());
}

void NGramMarkov::serializeToOstream(std::ostream &out) const {
  markov::NGramMarkov model;
  serialize(model);

  model.SerializeToOstream(&out);
}

void NGramMarkov::deserialize(const markov::NGramMarkov &in) {
  n_ = in.n();
  Graph::deserialize(in.graph());
}

void NGramMarkov::deserializeFromIstream(std::istream &in) {
  markov::NGramMarkov model;
  model.ParseFromIstream(&in);

  deserialize(model);
}

uint64_t NGramMarkov::makeContextId(const std::vector<uint64_t> &ids) {
  return XXH64(ids.data(), ids.size() * sizeof(uint64_t), 0);
}
