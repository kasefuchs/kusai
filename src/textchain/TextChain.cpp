#include "kusai/textchain/TextChain.hpp"

#include <google/protobuf/any.pb.h>
#include <xxhash.h>

#include <cstdint>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include "kusai/graph/AbstractGraph.hpp"
#include "kusai/proto/textchain.pb.h"

void TextChain::train(const std::vector<std::string>& sequences) const {
  std::vector<std::vector<NodeId> > nodeSequences;
  nodeSequences.reserve(sequences.size());

  for (const auto& text : sequences) {
    const auto tokens = tokenizer.encode(text);

    nodeSequences.push_back(tokens);
  }

  markov.train(nodeSequences);
}

std::vector<NodeId> TextChain::generateNodes(const std::string& context, const uint32_t limit) const {
  const auto seq = tokenizer.encode(context);

  return markov.generateNodes(seq, limit);
}

std::string TextChain::generateTokens(const std::string& context, const uint32_t limit) const {
  const auto seq = generateNodes(context, limit);

  return tokenizer.decode(seq);
}

void TextChain::serialize(google::protobuf::Any& out) const {
  textchain::TextChain container;
  markov.serialize(*container.mutable_markov());
  tokenizer.serialize(*container.mutable_tokenizer());

  out.PackFrom(container);
}

void TextChain::deserialize(const google::protobuf::Any& in) const {
  textchain::TextChain container;
  in.UnpackTo(&container);

  markov.deserialize(container.markov());
  tokenizer.deserialize(container.tokenizer());
}

void TextChain::serializeToOstream(std::ostream& out) const {
  google::protobuf::Any container;
  serialize(container);

  container.SerializeToOstream(&out);
}

void TextChain::deserializeFromIstream(std::istream& in) const {
  google::protobuf::Any container;
  container.ParseFromIstream(&in);

  deserialize(container);
}
