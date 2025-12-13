#include "TextChain.hpp"

#include "textchain.pb.h"

void TextChain::train(const std::vector<std::string> &sequences) {
  Markov::train({});

  std::vector<std::vector<graph::Node *> > nodeSequences;
  nodeSequences.reserve(sequences.size());

  for (const auto &text: sequences) {
    std::vector<graph::Node *> seq;
    std::istringstream stream(text);
    std::string token;

    while (stream >> token) {
      const uint32_t id = makeTokenId(token);
      auto *node = getOrAddNode(id);

      textchain::NodeMetadata meta;
      meta.set_value(token);
      node->mutable_metadata()->PackFrom(meta);

      seq.push_back(node);
    }

    if (!seq.empty()) nodeSequences.push_back(std::move(seq));
  }

  NGramMarkov::train(nodeSequences);
}

graph::Node *TextChain::nextNode(const std::string &context) const {
  std::vector<graph::Node *> nodes;
  std::istringstream stream(context);
  std::string token;

  while (stream >> token) {
    const auto id = makeTokenId(token);
    auto *node = getNode(id);
    nodes.push_back(node);
  }

  return NGramMarkov::nextNode(nodes);
}

std::string TextChain::nextToken(const std::string &context) const {
  const auto *node = nextNode(context);
  if (!node) return "";

  textchain::NodeMetadata meta;
  if (!node->metadata().UnpackTo(&meta)) return "";

  return meta.value();
}

uint32_t TextChain::makeTokenId(const std::string &token) {
  uint32_t hash = 0x811c9dc5;
  for (const unsigned char c: token) {
    hash ^= c;
    hash *= 0x01000193;
  }

  return hash;
}
