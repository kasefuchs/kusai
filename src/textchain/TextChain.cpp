#include "TextChain.hpp"
#include "markov.hpp"

textchain::Token &TextChain::startToken() {
  if (startToken_ == nullptr) startToken_ = &getOrAddTokenByValue("\x02");
  return *startToken_;
}

textchain::Token &TextChain::endToken() {
  if (endToken_ == nullptr) endToken_ = &getOrAddTokenByValue("\x03");
  return *endToken_;
}

textchain::Token *TextChain::getTokenByNode(const uint32_t id) const {
  const auto *node = getNode(id);

  markov::NodeMetadata meta;
  markov::unpackNodeMetadata(*node, &meta);

  return tokens_.at(meta.value()).get();
}

textchain::Token *TextChain::getTokenByNode(const graph::Node &node) const {
  return getTokenByNode(node.id());
}

textchain::Token *TextChain::getTokenByValue(const std::string &value) const {
  const auto it = tokenByValueIndex_.find(value);
  return it != tokenByValueIndex_.end() ? it->second : nullptr;
}

textchain::Token &TextChain::addToken(const uint32_t id, const std::string &value) {
  auto token = std::make_unique<textchain::Token>();

  token->set_id(id);
  token->set_value(value);

  const auto [it, _] = tokens_.emplace(token->id(), std::move(token));
  tokenByValueIndex_.emplace(it->second->value(), it->second.get());

  return *it->second;
}

textchain::Token &TextChain::addToken(const std::string &value) {
  return addToken(tokenIdGenerator_.next(), value);
}

textchain::Token &TextChain::getOrAddTokenByValue(const std::string &value) {
  if (auto *token = getTokenByValue(value)) return *token;
  return addToken(value);
}

void TextChain::train(const std::vector<std::string> &strings) {
  std::vector<std::vector<uint32_t> > sequences;
  sequences.reserve(strings.size());

  for (const auto &str: strings) {
    std::vector<uint32_t> sequence;

    std::istringstream iss(str);
    std::string word;

    sequence.push_back(startToken().id());
    while (iss >> word) sequence.push_back(getOrAddTokenByValue(word).id());
    sequence.push_back(endToken().id());

    sequences.push_back(std::move(sequence));
  }

  Markov::train(sequences);
}

graph::Node *TextChain::nextNode(const textchain::Token &current) const {
  const auto *currentNode = getNodeByValue(current.id());
  return Markov::nextNode(*currentNode);
}

textchain::Token *TextChain::nextToken(const textchain::Token &current) const {
  const auto *node = nextNode(current);
  if (!node) return nullptr;

  return getTokenByNode(*node);
}

void TextChain::serialize(textchain::TextChain &out) const {
  tokenIdGenerator_.serialize(*out.mutable_token_id_generator());

  Graph::serialize(*out.mutable_graph());

  for (const auto &[_, token]: tokens_) out.add_tokens()->CopyFrom(*token);
}

void TextChain::deserialize(const textchain::TextChain &in) {
  tokenIdGenerator_.deserialize(in.token_id_generator());

  Markov::deserialize(in.graph());

  tokens_.clear();
  startToken_ = endToken_ = nullptr;
  for (const auto &tokenProto: in.tokens()) addToken(tokenProto.id(), tokenProto.value()).CopyFrom(tokenProto);
}
