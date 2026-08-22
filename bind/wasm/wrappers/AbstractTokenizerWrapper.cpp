#include "AbstractTokenizerWrapper.hpp"

#include <emscripten/val.h>

#include <nlohmann/json.hpp>

namespace kusai::bind::wasm {
namespace em = emscripten;

nlohmann::json AbstractTokenizerWrapper::serialize() const {
  const auto js_val = call<em::val>("serialize");
  const auto str = em::val::global("JSON").call<std::string>("stringify", js_val);
  return nlohmann::json::parse(str);
}

bool AbstractTokenizerWrapper::deserialize(const nlohmann::json& data) {
  const auto js_val = em::val::global("JSON").call<em::val>("parse", data.dump());
  return call<bool>("deserialize", js_val);
}

std::vector<TokenId> AbstractTokenizerWrapper::encodeUnlocked(const std::string& text) {
  return call<std::vector<TokenId>>("_encode_unlocked", text);
}

std::string AbstractTokenizerWrapper::decodeUnlocked(const std::vector<TokenId>& text) {
  return call<std::string>("_decode_unlocked", text);
}
}  // namespace kusai::bind::wasm
