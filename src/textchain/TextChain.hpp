#pragma once

#include "Markov.hpp"

class TextChain {
 public:
  explicit TextChain(AbstractMarkov& markov) : markov(markov) {}

  AbstractMarkov& markov;

  [[nodiscard]] std::optional<std::string> getNodeToken(const NodeId& id) const;

  [[nodiscard]] std::vector<NodeId> contextNodes(const std::string& context) const;

  void train(const std::vector<std::string>& sequences) const;

  [[nodiscard]] std::optional<NodeId> nextNode(const std::string& context) const;

  [[nodiscard]] std::vector<NodeId> generateNodes(const std::string& context, uint32_t limit = INT8_MAX) const;

  [[nodiscard]] std::optional<std::string> nextToken(const std::string& context) const;

  [[nodiscard]] std::string generateTokens(const std::string& context, uint32_t limit = INT8_MAX,
                                           const std::string& breakValue = "") const;

 private:
  static NodeId makeTokenId(const std::string& token);
};
