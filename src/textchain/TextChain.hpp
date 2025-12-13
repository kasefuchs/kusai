#pragma once
#include "NGramMarkov.hpp"

class TextChain : public NGramMarkov {
public:
  explicit TextChain(const uint32_t n) : NGramMarkov(n) {}

  void train(const std::vector<std::string> &sequences);

  graph::Node *nextNode(const std::string &context) const;

  std::string nextToken(const std::string &context) const;

private:
  static uint32_t makeTokenId(const std::string &token);
};
