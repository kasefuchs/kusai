#include "TextChain.hpp"

#include <xxhash.h>

#include "textchain.pb.h"

graph::Node *TextChain::addNode(const std::string &token) const {
  const auto id = makeTokenId(token);
  auto *node = markov.graph.addNode(id);

  textchain::NodeMetadata meta;
  meta.set_value(token);
  node->mutable_metadata()->PackFrom(meta);

  return node;
}

graph::Node *TextChain::getNode(const std::string &token) const {
  const auto id = makeTokenId(token);
  return markov.graph.getNode(id);
}

graph::Node *TextChain::getOrAddNode(const std::string &token) const {
  if (auto *node = getNode(token))
    return node;
  return addNode(token);
}

std::vector<graph::Node *> TextChain::contextNodes(const std::string &context) const {
  std::vector<graph::Node *> seq;
  std::istringstream stream(context);
  std::string token;

  while (stream >> token) {
    auto *node = getOrAddNode(token);
    seq.push_back(node);
  }

  return seq;
}

void TextChain::train(const std::vector<std::string> &sequences) const {
  std::vector<std::vector<graph::Node *>> nodeSequences;
  nodeSequences.reserve(sequences.size());

  for (const auto &text : sequences) {
    if (auto seq = contextNodes(text); !seq.empty()) {
      nodeSequences.push_back(std::move(seq));
    }
  }

  markov.train(nodeSequences);
}

graph::Node *TextChain::nextNode(const std::string &context) const {
  const auto seq = contextNodes(context);
  return markov.nextNode(seq);
}

std::vector<graph::Node *> TextChain::generateNodes(const std::string &context, const uint32_t limit) const {
  const auto seq = contextNodes(context);
  return markov.generateNodes(seq, limit);
}

std::string TextChain::nextToken(const std::string &context) const {
  const auto *node = nextNode(context);
  if (!node)
    return "";

  textchain::NodeMetadata meta;
  if (!node->metadata().UnpackTo(&meta))
    return "";

  return meta.value();
}

std::string TextChain::generateTokens(const std::string &context, const uint32_t limit,
                                      const std::string &breakValue) const {
  std::string result;
  for (const auto nodes = generateNodes(context, limit); const auto *node : nodes) {
    textchain::NodeMetadata meta;
    if (!node || !node->metadata().UnpackTo(&meta))
      continue;

    if (!result.empty())
      result += ' ';

    result += meta.value();

    if (meta.value() == breakValue)
      break;
  }

  return result;
}

uint64_t TextChain::makeTokenId(const std::string &token) { return XXH64(&token[0], token.size(), 0); }
