#pragma once

#include <emscripten/bind.h>

#include "kusai/serializable/AbstractSerializable.hpp"

namespace em = emscripten;
namespace kusai::bind::wasm {
class AbstractSerializableWrapper : public em::wrapper<AbstractSerializable> {
 public:
  EMSCRIPTEN_WRAPPER(AbstractSerializableWrapper);

  [[nodiscard]] nlohmann::json serialize() const override;
  bool deserialize(const nlohmann::json& data) override;
};
}  // namespace kusai::bind::wasm
