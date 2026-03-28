#pragma once

#include <absl/container/flat_hash_map.h>

#include "AbstractTokenizer.hpp"

namespace kusai {
class SimpleTokenizer : public AbstractTokenizer {
 public:
  [[nodiscard]] std::vector<TokenId> encodeUnlocked(const std::string& context) override;

  [[nodiscard]] std::string decodeUnlocked(const std::vector<TokenId>& context) override;

  [[nodiscard]] nlohmann::json serialize() const override;
  void deserialize(const nlohmann::json& data) override;

 private:
  absl::flat_hash_map<TokenId, std::string> vocabulary_;

  [[nodiscard]] static TokenId makeTokenId(const std::string& token);
};
}  // namespace kusai
