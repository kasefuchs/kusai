#pragma once

#include <absl/container/flat_hash_map.h>

#include "AbstractTokenizer.hpp"

namespace kusai {
class SimpleTokenizer : public AbstractTokenizer {
 public:
  [[nodiscard]] std::vector<TokenId> encodeUnlocked(const std::string& context) override;

  [[nodiscard]] std::string decodeUnlocked(const std::vector<TokenId>& context) override;

  void serialize(pugi::xml_node& self) const override;

  void deserialize(const pugi::xml_node& self) override;

 private:
  absl::flat_hash_map<TokenId, std::string> vocabulary_;

  [[nodiscard]] static TokenId makeTokenId(const std::string& token);

  [[nodiscard]] std::string tagName() const override;
};
}  // namespace kusai
