#include <emscripten/bind.h>

#include "bindings.hpp"

namespace em = emscripten;
namespace kusai::bind::wasm {
EMSCRIPTEN_BINDINGS(kusai) {
  bind_serializable();
  bind_tokenizer();
}
}  // namespace kusai::bind::wasm
