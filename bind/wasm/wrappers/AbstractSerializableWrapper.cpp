#include "AbstractSerializableWrapper.hpp"

#include <emscripten/val.h>

namespace kusai::bind::wasm {
namespace em = emscripten;

nlohmann::json AbstractSerializableWrapper::serialize() const {
  const auto js_val = call<em::val>("serialize");
  const auto str = em::val::global("JSON").call<std::string>("stringify", js_val);
  return nlohmann::json::parse(str);
}

bool AbstractSerializableWrapper::deserialize(const nlohmann::json& data) {
  const auto js_val = em::val::global("JSON").call<em::val>("parse", data.dump());
  return call<bool>("deserialize", js_val);
}
}  // namespace kusai::bind::wasm
