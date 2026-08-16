#include "kusai/tokenizer/SimpleTokenizer.hpp"

#include <xxhash.h>

#include <exception>
#include <iterator>
#include <mutex>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "kusai/tokenizer/AbstractTokenizer.hpp"

namespace kusai {
std::vector<TokenId> SimpleTokenizer::encodeUnlocked(const std::string& context) {
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

std::string SimpleTokenizer::decodeUnlocked(const std::vector<TokenId>& context) {
  std::vector<std::string> tokens;
  tokens.reserve(context.size());

  for (auto id : context) {
    if (auto it = vocabulary_.find(id); it != vocabulary_.end()) {
      tokens.push_back(it->second);
    }
  }

  if (tokens.empty()) {
    return {};
  }

  return std::accumulate(std::next(tokens.begin()), tokens.end(), tokens.front(),
                         [](const std::string& a, const std::string& b) { return a + " " + b; });
}

nlohmann::json SimpleTokenizer::serialize() const {
  std::shared_lock lock(mutex_);
  nlohmann::json vocabJson = nlohmann::json::object();
  for (const auto& [id, token] : vocabulary_) {
    vocabJson[std::to_string(id)] = token;
  }

  return {{"vocabulary", vocabJson}};
}

bool SimpleTokenizer::deserialize(const nlohmann::json& data) {
  std::unique_lock lock(mutex_);
  vocabulary_.clear();

  try {
    for (const auto& vocabJson = data.at("vocabulary"); auto& [key, value] : vocabJson.items()) {
      const TokenId id = std::stoull(key);
      vocabulary_.emplace(id, value.get<std::string>());
    }
  } catch (const std::exception&) {
    return false;
  }

  return true;
}

TokenId SimpleTokenizer::makeTokenId(const std::string& token) { return XXH64(&token[0], token.size(), 0); }
}  // namespace kusai
