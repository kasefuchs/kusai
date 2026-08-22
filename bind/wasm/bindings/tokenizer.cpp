#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <memory>

#include "bindings.hpp"
#include "kusai/tokenizer/AbstractTokenizer.hpp"
#include "kusai/tokenizer/SimpleTokenizer.hpp"
#include "wrappers/AbstractTokenizerWrapper.hpp"

namespace em = emscripten;
namespace kusai::bind::wasm {
void bind_tokenizer() {
  em::register_vector<TokenId>("VectorTokenId");

  em::class_<AbstractTokenizer>("AbstractTokenizer")
      .smart_ptr<std::shared_ptr<AbstractTokenizer>>("AbstractTokenizer")
      .allow_subclass<AbstractTokenizerWrapper>("AbstractTokenizerWrapper")
      .function("encode", &AbstractTokenizer::encode)
      .function("decode", &AbstractTokenizer::decode)
      .function("serialize", &serialize_to_js<AbstractTokenizer>)
      .function("deserialize", &deserialize_from_js<AbstractTokenizer>);

  em::class_<SimpleTokenizer, em::base<AbstractTokenizer>>("SimpleTokenizer")
      .smart_ptr_constructor("SimpleTokenizer", &std::make_shared<SimpleTokenizer>);
}
}  // namespace kusai::bind::wasm
