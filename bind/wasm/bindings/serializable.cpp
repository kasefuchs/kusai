#include <emscripten/bind.h>
#include <emscripten/val.h>

#include "bindings.hpp"
#include "kusai/serializable/AbstractSerializable.hpp"
#include "wrappers/AbstractSerializableWrapper.hpp"

namespace em = emscripten;
namespace kusai::bind::wasm {
void bind_serializable() {
  em::class_<AbstractSerializable>("AbstractSerializable")
      .smart_ptr<std::shared_ptr<AbstractSerializable>>("AbstractSerializable")
      .allow_subclass<AbstractSerializableWrapper>("AbstractSerializableWrapper")
      .function("serialize", &serialize_to_js<AbstractSerializable>)
      .function("deserialize", &deserialize_from_js<AbstractSerializable>);
}
}  // namespace kusai::bind::wasm
