#pragma once

#include <absl/container/flat_hash_map.h>

#include "AbstractTokenizer.hpp"

class SimpleTokenizer : public AbstractTokenizer {
 public:
  [[nodiscard]] std::vector<TokenId> encode(const std::string& context) override;

  [[nodiscard]] std::string decode(const std::vector<TokenId>& context) override;

  void serialize(pugi::xml_node& self) const override;

  void deserialize(const pugi::xml_node& self) override;

  [[nodiscard]] std::string tagName() const override;

 private:
  absl::flat_hash_map<TokenId, std::string> vocabulary_;

  [[nodiscard]] static TokenId makeTokenId(const std::string& token);
};
