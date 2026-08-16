#pragma once

#include <unordered_map>

#include "AbstractTokenizer.hpp"

namespace kusai {
class SimpleTokenizer : public AbstractTokenizer {
 public:
  [[nodiscard]] std::vector<TokenId> encodeUnlocked(const std::string& context) override;

  [[nodiscard]] std::string decodeUnlocked(const std::vector<TokenId>& context) override;

  [[nodiscard]] nlohmann::json serialize() const override;
  bool deserialize(const nlohmann::json& data) override;

 private:
  std::unordered_map<TokenId, std::string> vocabulary_;

  [[nodiscard]] static TokenId makeTokenId(const std::string& token);
};
}  // namespace kusai
