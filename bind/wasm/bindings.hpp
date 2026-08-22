#pragma once

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <nlohmann/json.hpp>

namespace em = emscripten;
namespace kusai::bind::wasm {
template <typename T>
em::val serialize_to_js(const T& self) {
  const auto dumped = self.serialize().dump();
  return em::val::global("JSON").call<em::val>("parse", dumped);
}

template <typename T>
bool deserialize_from_js(T& self, const em::val& data) {
  try {
    const auto json_str = em::val::global("JSON").call<std::string>("stringify", data);
    return self.deserialize(nlohmann::json::parse(json_str));
  } catch (...) {
    return false;
  }
}

void bind_serializable();
void bind_tokenizer();
}  // namespace kusai::bind::wasm
