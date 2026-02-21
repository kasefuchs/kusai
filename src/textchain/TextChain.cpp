#include "kusai/textchain/TextChain.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include "kusai/graph/AbstractGraph.hpp"
#include "kusai/graph/Node.hpp"

namespace kusai {
void TextChain::train(const std::vector<std::string>& sequences) const {
  std::vector<std::vector<NodeId> > nodeSequences;
  nodeSequences.reserve(sequences.size());

  for (const auto& text : sequences) {
    const auto tokens = tokenizer.encode(text);

    nodeSequences.push_back(tokens);
  }

  markov.train(nodeSequences);
}

std::vector<TokenId> TextChain::generateSequence(const std::string& context, const uint32_t limit) const {
  const auto seq = tokenizer.encode(context);

  return markov.generateSequence(seq, limit);
}

std::string TextChain::generateText(const std::string& context, const uint32_t limit) const {
  const auto seq = generateSequence(context, limit);

  return tokenizer.decode(seq);
}

void TextChain::serialize(pugi::xml_node& self) const {
  markov.serializeToParent(self);
  tokenizer.serializeToParent(self);
}

void TextChain::deserialize(const pugi::xml_node& self) {
  markov.deserializeFromParent(self);
  tokenizer.deserializeFromParent(self);
}

std::string TextChain::tagName() const { return "TextChain"; }
}  // namespace kusai
