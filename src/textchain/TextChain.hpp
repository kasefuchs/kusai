#pragma once

#include "AbstractMarkov.hpp"
#include "AbstractTokenizer.hpp"

class TextChain {
 public:
  explicit TextChain(AbstractMarkov& markov, AbstractTokenizer& tokenizer) : markov(markov), tokenizer(tokenizer) {}

  AbstractMarkov& markov;
  AbstractTokenizer& tokenizer;

  void train(const std::vector<std::string>& sequences) const;

  [[nodiscard]] std::vector<NodeId> generateNodes(const std::string& context, uint32_t limit = INT8_MAX) const;
  [[nodiscard]] std::string generateTokens(const std::string& context, uint32_t limit = INT8_MAX) const;

  void serialize(google::protobuf::Any& out) const;
  void deserialize(const google::protobuf::Any& in) const;

  void serializeToOstream(std::ostream& out) const;
  void deserializeFromIstream(std::istream& in) const;
};
