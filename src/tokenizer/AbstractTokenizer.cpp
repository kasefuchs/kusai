#include "kusai/tokenizer/AbstractTokenizer.hpp"

#include <mutex>
#include <shared_mutex>

namespace kusai {
std::vector<TokenId> AbstractTokenizer::encode(const std::string& text) {
  std::unique_lock lock(mutex_);
  return encodeUnlocked(text);
}

std::string AbstractTokenizer::decode(const std::vector<TokenId>& text) {
  std::shared_lock lock(mutex_);
  return decodeUnlocked(text);
}
}  // namespace kusai
