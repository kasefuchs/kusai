#pragma once

#include <google/protobuf/any.pb.h>

#include <cstdint>
#include <string>
#include <vector>

using TokenId = std::uint64_t;

class AbstractTokenizer {
 public:
  virtual ~AbstractTokenizer() = default;

  [[nodiscard]] virtual std::vector<TokenId> encode(const std::string& text) = 0;

  [[nodiscard]] virtual std::string decode(const std::vector<TokenId>& text) = 0;

  virtual void serialize(google::protobuf::Any& out) const = 0;

  virtual void deserialize(const google::protobuf::Any& in) = 0;

 protected:
  explicit AbstractTokenizer() = default;
};
