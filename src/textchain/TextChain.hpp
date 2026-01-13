#pragma once
#include "Markov.hpp"

class TextChain {
public:
  explicit TextChain(Markov &markov) : markov(markov) {}

  Markov &markov;

  graph::Node *addNode(const std::string &token) const;

  graph::Node *getNode(const std::string &token) const;

  graph::Node *getOrAddNode(const std::string &token) const;

  std::vector<graph::Node *> contextNodes(const std::string &context) const;

  void train(const std::vector<std::string> &sequences) const;

  graph::Node *nextNode(const std::string &context) const;

  std::vector<graph::Node *> generateNodes(const std::string &context, uint32_t limit) const;

  std::string nextToken(const std::string &context) const;

  std::string generateTokens(const std::string &context, uint32_t limit) const;

private:
  static uint64_t makeTokenId(const std::string &token);
};
