// Copyright (c) Kasefuchs
// SPDX-License-Identifier: MIT

#include "TextChain.hpp"

#include "markov.hpp"

TextChain::TextChain() {
  startToken_ = addToken("\x02");
  endToken_ = addToken("\x03");
}

textchain::Token * TextChain::startToken() const {
  return startToken_;
}

textchain::Token * TextChain::endToken() const {
  return endToken_;
}

textchain::Token *TextChain::getTokenByNode(const uint32_t id) const {
  const auto * node = getNode(id);

  markov::NodeMetadata meta;
  markov::unpackNodeMetadata(node, &meta);

  return tokens_.at(meta.value()).get();
}

textchain::Token *TextChain::getTokenByNode(const graph::Node *node) const {
  return getTokenByNode(node->id());
}

textchain::Token *TextChain::getTokenByValue(const std::string &value) const {
  for (const auto &[_, token]: tokens_) {
    if (token->value() == value) return token.get();
  }

  return nullptr;
}

textchain::Token *TextChain::addToken(const std::string &value) {
  auto token = std::make_unique<textchain::Token>();

  token->set_id(lastTokenId_++);
  token->set_value(value);

  const auto [it, _] = tokens_.emplace(token->id(), std::move(token));
  return it->second.get();
}

void TextChain::train(const std::vector<std::string> &strings) {
  std::vector<std::vector<uint32_t> > sequences;
  sequences.reserve(strings.size());

  for (const auto &str: strings) {
    std::vector<uint32_t> sequence;

    sequence.push_back(startToken_->id());

    std::istringstream iss(str);
    std::string word;

    while (iss >> word) {
      const auto *token = getTokenByValue(word);
      if (!token) token = addToken(word);
      sequence.push_back(token->id());
    }

    sequence.push_back(endToken_->id());

    sequences.push_back(std::move(sequence));
  }

  Markov::train(sequences);
}

textchain::Token *TextChain::nextToken(const textchain::Token *current) const {
  const auto *currentNode = getNodeByValue(current->id());
  const auto *nextNode = Markov::nextNode(currentNode);
  if (!nextNode) return nullptr;

  return getTokenByNode(nextNode);
}

void TextChain::serialize(textchain::TextChain *out) const {
  Graph::serialize(out->mutable_graph());
}

void TextChain::deserialize(const textchain::TextChain *in) {
  Graph::deserialize(&in->graph());
}
