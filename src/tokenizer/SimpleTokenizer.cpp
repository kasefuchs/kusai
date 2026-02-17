#include "SimpleTokenizer.hpp"

#include <absl/strings/str_join.h>
#include <xxhash.h>

#include "tokenizer.pb.h"

std::vector<TokenId> SimpleTokenizer::encode(const std::string& context) {
  std::vector<TokenId> seq;
  std::istringstream stream(context);

  std::string token;
  while (stream >> token) {
    const auto id = makeTokenId(token);
    vocabulary_.try_emplace(id, token);

    seq.push_back(id);
  }

  return seq;
}

std::string SimpleTokenizer::decode(const std::vector<TokenId>& context) {
  std::vector<std::string> tokens;
  tokens.reserve(context.size());

  for (auto id : context) {
    if (auto it = vocabulary_.find(id); it != vocabulary_.end()) {
      tokens.push_back(it->second);
    }
  }

  return absl::StrJoin(tokens, " ");
}

void SimpleTokenizer::serialize(google::protobuf::Any& out) const {
  tokenizer::SimpleTokenizer container;
  for (const auto& [id, token] : vocabulary_) {
    container.mutable_vocabulary()->emplace(id, token);
  }

  out.PackFrom(container);
}

void SimpleTokenizer::deserialize(const google::protobuf::Any& in) {
  tokenizer::SimpleTokenizer container;
  in.UnpackTo(&container);

  vocabulary_.clear();
  vocabulary_.reserve(container.vocabulary().size());
  for (const auto& [id, token] : container.vocabulary()) {
    vocabulary_.emplace(id, token);
  }
}

TokenId SimpleTokenizer::makeTokenId(const std::string& token) { return XXH64(&token[0], token.size(), 0); }
