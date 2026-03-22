#include "kusai/textchain/TextChain.hpp"

#include <cstdint>
#include <mutex>
#include <string>
#include <vector>

#include "kusai/graph/AbstractGraph.hpp"
#include "kusai/graph/Node.hpp"

namespace kusai {
void TextChain::train(const std::vector<std::string>& sequences) const {
  std::unique_lock lock(mutex_);
  std::vector<std::vector<NodeId> > nodeSequences;
  nodeSequences.reserve(sequences.size());

  for (const auto& text : sequences) {
    const auto tokens = tokenizer->encode(text);

    nodeSequences.push_back(tokens);
  }

  markov->train(nodeSequences);
}

std::vector<TokenId> TextChain::generateSequence(const std::string& context, const uint32_t limit) const {
  std::shared_lock lock(mutex_);
  return generateSequenceUnlocked(context, limit);
}

std::string TextChain::generateText(const std::string& context, const uint32_t limit) const {
  std::shared_lock lock(mutex_);
  const auto seq = generateSequenceUnlocked(context, limit);

  return tokenizer->decode(seq);
}

void TextChain::serialize(pugi::xml_node& self) const {
  std::shared_lock lock(mutex_);
  markov->serializeToParent(self);
  tokenizer->serializeToParent(self);
}

void TextChain::deserialize(const pugi::xml_node& self) {
  std::unique_lock lock(mutex_);
  markov->deserializeFromParent(self);
  tokenizer->deserializeFromParent(self);
}

std::string TextChain::tagName() const { return "TextChain"; }

std::vector<TokenId> TextChain::generateSequenceUnlocked(const std::string& context, uint32_t limit) const {
  const auto seq = tokenizer->encode(context);

  return markov->generateSequence(seq, limit);
}
}  // namespace kusai
