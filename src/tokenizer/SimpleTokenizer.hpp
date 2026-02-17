#pragma once

#include <absl/container/flat_hash_map.h>

#include "AbstractTokenizer.hpp"

class SimpleTokenizer : public AbstractTokenizer {
 public:
  explicit SimpleTokenizer() : AbstractTokenizer() {}

  std::vector<TokenId> encode(const std::string& context) override;
  std::string decode(const std::vector<TokenId>& context) override;

  void serialize(google::protobuf::Any& out) const override;
  void deserialize(const google::protobuf::Any& in) override;

 private:
  absl::flat_hash_map<TokenId, std::string> vocabulary_;

  static TokenId makeTokenId(const std::string& token);
};
