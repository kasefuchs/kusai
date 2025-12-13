#pragma once
#include "NGramMarkov.hpp"

class TextChain : public NGramMarkov {
public:
  explicit TextChain(const uint32_t n) : NGramMarkov(n) {
  }

  graph::Node *addNode(const std::string &token);

  graph::Node *getNode(const std::string &token) const;

  graph::Node *getOrAddNode(const std::string &token);

  std::vector<graph::Node *> contextNodes(const std::string &context);

  void train(const std::vector<std::string> &sequences);

  graph::Node *nextNode(const std::string &context);

  std::string nextToken(const std::string &context);

private:
  static uint32_t makeTokenId(const std::string &token);
};
