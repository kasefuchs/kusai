#pragma once

#include "kusai/markov/AbstractMarkov.hpp"
#include "kusai/tokenizer/AbstractTokenizer.hpp"

class TextChain : public Serializable {
 public:
  explicit TextChain(AbstractMarkov& markov, AbstractTokenizer& tokenizer) : markov(markov), tokenizer(tokenizer) {}

  AbstractMarkov& markov;
  AbstractTokenizer& tokenizer;

  void train(const std::vector<std::string>& sequences) const;

  [[nodiscard]] std::vector<NodeId> generateNodes(const std::string& context, uint32_t limit = INT8_MAX) const;

  [[nodiscard]] std::string generateTokens(const std::string& context, uint32_t limit = INT8_MAX) const;

  void serialize(pugi::xml_node& self) const override;

  void deserialize(const pugi::xml_node& self) override;

  [[nodiscard]] std::string tagName() const override;
};
