#pragma once

#include "kusai/markov/AbstractMarkov.hpp"
#include "kusai/tokenizer/AbstractTokenizer.hpp"

namespace kusai {
class TextChain : public AbstractSerializable {
 public:
  explicit TextChain(const std::shared_ptr<AbstractMarkov>& markov, const std::shared_ptr<AbstractTokenizer>& tokenizer)
      : markov(markov), tokenizer(tokenizer) {}

  std::shared_ptr<AbstractMarkov> markov;
  std::shared_ptr<AbstractTokenizer> tokenizer;

  void train(const std::vector<std::string>& sequences) const;

  [[nodiscard]] std::vector<TokenId> generateSequence(const std::string& context, uint32_t limit = INT8_MAX) const;

  [[nodiscard]] std::string generateText(const std::string& context, uint32_t limit = INT8_MAX) const;

  void serialize(pugi::xml_node& self) const override;

  void deserialize(const pugi::xml_node& self) override;

 private:
  mutable std::shared_mutex mutex_;

  [[nodiscard]] std::vector<TokenId> generateSequenceUnlocked(const std::string& context,
                                                              uint32_t limit = INT8_MAX) const;

  [[nodiscard]] std::string tagName() const override;
};
}  // namespace kusai
