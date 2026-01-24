#include "TextChain.hpp"

#include <absl/strings/str_join.h>
#include <xxhash.h>

#include <cstdint>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "AbstractGraph.hpp"
#include "graph.pb.h"
#include "textchain.pb.h"

NodeId TextChain::ensureNode(const std::string& token) const {
  const auto id = makeTokenId(token);
  if (!markov.graph.hasNode(id)) {
    markov.graph.modifyNode(markov.graph.ensureNode(id), [&](graph::Node& node) {
      textchain::NodeMetadata meta;
      meta.set_value(token);
      node.mutable_metadata()->PackFrom(meta);
    });
  }

  return id;
}

std::optional<std::string> TextChain::getNodeToken(const NodeId& id) const {
  const auto node = markov.graph.getNode(id);
  if (!node) {
    return std::nullopt;
  }

  textchain::NodeMetadata meta;
  if (!node->metadata().UnpackTo(&meta)) {
    return std::nullopt;
  }

  return meta.value();
}

std::vector<NodeId> TextChain::contextNodes(const std::string& context) const {
  std::vector<NodeId> seq;
  std::istringstream stream(context);
  std::string token;

  while (stream >> token) {
    auto node = ensureNode(token);
    seq.push_back(node);
  }

  return seq;
}

void TextChain::train(const std::vector<std::string>& sequences) const {
  std::vector<std::vector<NodeId>> nodeSequences;
  nodeSequences.reserve(sequences.size());

  for (const auto& text : sequences) {
    if (auto seq = contextNodes(text); !seq.empty()) {
      nodeSequences.push_back(std::move(seq));
    }
  }

  markov.train(nodeSequences);
}

std::optional<NodeId> TextChain::nextNode(const std::string& context) const {
  const auto seq = contextNodes(context);

  return markov.nextNode(seq);
}

std::vector<NodeId> TextChain::generateNodes(const std::string& context, const uint32_t limit) const {
  const auto seq = contextNodes(context);

  return markov.generateNodes(seq, limit);
}

std::optional<std::string> TextChain::nextToken(const std::string& context) const {
  if (const auto id = nextNode(context)) {
    if (auto tok = getNodeToken(*id)) {
      return tok;
    }
  }

  return std::nullopt;
}

std::string TextChain::generateTokens(const std::string& context, const uint32_t limit,
                                      const std::string& breakValue) const {
  std::vector<std::string> tokens;
  for (NodeId id : generateNodes(context, limit)) {
    const auto tok = getNodeToken(id);
    if (!tok || *tok == breakValue) {
      break;
    }

    tokens.push_back(*tok);
  }

  return absl::StrJoin(tokens, " ");
}

NodeId TextChain::makeTokenId(const std::string& token) { return XXH64(&token[0], token.size(), 0); }
