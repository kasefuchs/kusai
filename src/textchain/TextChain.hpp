// Copyright (c) Kasefuchs
// SPDX-License-Identifier: MIT

#pragma once

#include "Markov.hpp"
#include "textchain.pb.h"

class TextChain : public Markov {
public:
  TextChain();

  textchain::Token *startToken() const;

  textchain::Token *endToken() const;

  textchain::Token *getTokenByNode(uint32_t id) const;

  textchain::Token *getTokenByNode(const graph::Node *node) const;

  ~TextChain() = default;

  textchain::Token *addToken(const std::string &value);

  void train(const std::vector<std::string> &strings);

  textchain::Token *nextToken(const textchain::Token *current) const;

  textchain::Token *getTokenByValue(const std::string &value) const;

  void serialize(textchain::TextChain *out) const;

  void deserialize(const textchain::TextChain *in);

private:
  uint32_t lastTokenId_ = 1;
  textchain::Token *startToken_, *endToken_;

  std::unordered_map<uint32_t, std::unique_ptr<textchain::Token> > tokens_;
};
