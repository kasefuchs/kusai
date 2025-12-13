#include "TextChain.hpp"

#include "hash.hpp"
#include "textchain.pb.h"

graph::Node *TextChain::addNode(const std::string &token) {
  const uint32_t id = makeTokenId(token);
  auto *node = Graph::addNode(id);

  textchain::NodeMetadata meta;
  meta.set_value(token);
  node->mutable_metadata()->PackFrom(meta);

  return node;
}

graph::Node *TextChain::getNode(const std::string &token) const {
  const uint32_t id = makeTokenId(token);
  return Graph::getNode(id);
}

graph::Node *TextChain::getOrAddNode(const std::string &token) {
  if (auto *node = getNode(token)) return node;
  return addNode(token);
}

std::vector<graph::Node *> TextChain::contextNodes(const std::string &context) {
  std::vector<graph::Node *> seq;
  std::istringstream stream(context);
  std::string token;

  while (stream >> token) {
    auto *node = getOrAddNode(token);
    seq.push_back(node);
  }

  return seq;
}

void TextChain::train(const std::vector<std::string> &sequences) {
  Markov::train({});

  std::vector<std::vector<graph::Node *> > nodeSequences;
  nodeSequences.reserve(sequences.size());

  for (const auto &text: sequences) {
    if (const auto seq = contextNodes(text); !seq.empty()) nodeSequences.push_back(seq);
  }

  NGramMarkov::train(nodeSequences);
}

graph::Node *TextChain::nextNode(const std::string &context) {
  const auto seq = contextNodes(context);

  return NGramMarkov::nextNode(seq);
}

std::string TextChain::nextToken(const std::string &context) {
  const auto *node = nextNode(context);
  if (!node) return "";

  textchain::NodeMetadata meta;
  if (!node->metadata().UnpackTo(&meta)) return "";

  return meta.value();
}

uint32_t TextChain::makeTokenId(const std::string &token) {
  return util::hash::fnv1a(token.data(), token.size());
}
