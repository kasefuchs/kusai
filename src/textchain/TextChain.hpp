#pragma once

#include "Markov.hpp"

class TextChain {
public:
  explicit TextChain(AbstractMarkov &markov) : markov(markov) {}

  AbstractMarkov &markov;

  [[nodiscard]] graph::Node *addNode(const std::string &token) const;

  [[nodiscard]] graph::Node *getNode(const std::string &token) const;

  [[nodiscard]] graph::Node *getOrAddNode(const std::string &token) const;

  [[nodiscard]] std::vector<graph::Node *> contextNodes(const std::string &context) const;

  void train(const std::vector<std::string> &sequences) const;

  [[nodiscard]] graph::Node *nextNode(const std::string &context) const;

  [[nodiscard]] std::vector<graph::Node *> generateNodes(const std::string &context, uint32_t limit = INT8_MAX) const;

  [[nodiscard]] std::string nextToken(const std::string &context) const;

  [[nodiscard]] std::string generateTokens(const std::string &context, uint32_t limit = INT8_MAX,
                                           const std::string &breakValue = "") const;

private:
  static uint64_t makeTokenId(const std::string &token);
};
