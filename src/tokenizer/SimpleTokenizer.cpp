#include "kusai/tokenizer/SimpleTokenizer.hpp"

#include <absl/strings/str_join.h>
#include <xxhash.h>

#include <sstream>
#include <string>
#include <vector>

#include "kusai/tokenizer/AbstractTokenizer.hpp"

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

void SimpleTokenizer::serialize(pugi::xml_node& self) const {
  for (auto vocabNode = self.append_child("Vocabulary"); const auto& [id, token] : vocabulary_) {
    auto tokenNode = vocabNode.append_child("Token");

    tokenNode.append_attribute("id") = id;
    tokenNode.text() = token.c_str();
  }
}

void SimpleTokenizer::deserialize(const pugi::xml_node& self) {
  for (const auto& tokenNode : self.child("Vocabulary").children("Token")) {
    const auto id = tokenNode.attribute("id").as_ullong();
    const auto text = tokenNode.text().as_string();

    vocabulary_.emplace(id, text);
  }
}

std::string SimpleTokenizer::tagName() const { return "SimpleTokenizer"; }

TokenId SimpleTokenizer::makeTokenId(const std::string& token) { return XXH64(&token[0], token.size(), 0); }
