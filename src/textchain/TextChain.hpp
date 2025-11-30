#pragma once

#include "Markov.hpp"
#include "textchain.pb.h"

class TextChain : public Markov {
public:
  TextChain() = default;

  ~TextChain() = default;

  textchain::Token &startToken();

  textchain::Token &endToken();

  textchain::Token *getTokenByNode(uint32_t id) const;

  textchain::Token *getTokenByNode(const graph::Node &node) const;

  textchain::Token &addToken(const std::string &value);

  textchain::Token &getOrAddTokenByValue(const std::string &value);

  void train(const std::vector<std::string> &strings);

  graph::Node *nextNode(const textchain::Token &current) const;

  textchain::Token *nextToken(const textchain::Token &current) const;

  textchain::Token *getTokenByValue(const std::string &value) const;

  textchain::Token &addToken(uint32_t id, const std::string &value);

  void serialize(textchain::TextChain &out) const;

  void deserialize(const textchain::TextChain &in);

private:
  IdGenerator tokenIdGenerator_;
  textchain::Token *startToken_ = nullptr, *endToken_ = nullptr;
  std::unordered_map<uint32_t, std::unique_ptr<textchain::Token> > tokens_;
  std::unordered_map<std::string, textchain::Token *> tokenByValueIndex_;
};
