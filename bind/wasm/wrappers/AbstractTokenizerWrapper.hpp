#pragma once

#include <emscripten/bind.h>

#include "kusai/tokenizer/AbstractTokenizer.hpp"

namespace em = emscripten;
namespace kusai::bind::wasm {
class AbstractTokenizerWrapper : public em::wrapper<AbstractTokenizer> {
 public:
  EMSCRIPTEN_WRAPPER(AbstractTokenizerWrapper);

  [[nodiscard]] nlohmann::json serialize() const override;
  bool deserialize(const nlohmann::json& data) override;

 protected:
  std::vector<TokenId> encodeUnlocked(const std::string& text) override;
  std::string decodeUnlocked(const std::vector<TokenId>& text) override;
};
}  // namespace kusai::bind::wasm
