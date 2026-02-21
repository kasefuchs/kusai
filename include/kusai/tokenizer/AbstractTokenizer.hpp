#pragma once

#include <cstdint>
#include <pugixml.hpp>
#include <string>
#include <vector>

#include "kusai/common/Serializable.hpp"

using TokenId = std::uint64_t;

class AbstractTokenizer : public Serializable {
 public:
  ~AbstractTokenizer() override = default;

  [[nodiscard]] virtual std::vector<TokenId> encode(const std::string& text) = 0;

  [[nodiscard]] virtual std::string decode(const std::vector<TokenId>& text) = 0;

 protected:
  explicit AbstractTokenizer() = default;
};
