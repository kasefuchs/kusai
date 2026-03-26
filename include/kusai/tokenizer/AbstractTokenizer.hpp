#pragma once

#include <cstdint>
#include <pugixml.hpp>
#include <shared_mutex>
#include <string>
#include <vector>

#include "kusai/common/AbstractSerializable.hpp"
#include "kusai/graph/Node.hpp"

namespace kusai {
using TokenId = NodeId;

class AbstractTokenizer : public AbstractSerializable {
 public:
  ~AbstractTokenizer() override = default;

  [[nodiscard]] std::vector<TokenId> encode(const std::string& text);

  [[nodiscard]] std::string decode(const std::vector<TokenId>& text);

 protected:
  mutable std::shared_mutex mutex_;

  explicit AbstractTokenizer() = default;

  [[nodiscard]] virtual std::vector<TokenId> encodeUnlocked(const std::string& text) = 0;

  [[nodiscard]] virtual std::string decodeUnlocked(const std::vector<TokenId>& text) = 0;
};
}  // namespace kusai
