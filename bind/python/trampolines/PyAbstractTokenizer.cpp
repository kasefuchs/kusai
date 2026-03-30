#include "PyAbstractTokenizer.hpp"

namespace kusai::bind::python {
nlohmann::json PyAbstractTokenizer::serialize() const {
  PYBIND11_OVERRIDE_PURE(nlohmann::json, AbstractTokenizer, serialize);
}

bool PyAbstractTokenizer::deserialize(const nlohmann::json& data) {
  PYBIND11_OVERRIDE_PURE(bool, AbstractTokenizer, deserialize, data);
}

std::vector<TokenId> PyAbstractTokenizer::encodeUnlocked(const std::string& text) {
  PYBIND11_OVERRIDE_PURE_NAME(std::vector<TokenId>, AbstractTokenizer, "_encode_unlocked", encodeUnlocked, text);
}

std::string PyAbstractTokenizer::decodeUnlocked(const std::vector<TokenId>& text) {
  PYBIND11_OVERRIDE_PURE_NAME(std::string, AbstractTokenizer, "_decode_unlocked", decodeUnlocked, text);
}
}  // namespace kusai::bind::python
