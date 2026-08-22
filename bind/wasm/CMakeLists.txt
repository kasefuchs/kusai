add_executable(bind-wasm
  module.cpp
  bindings.hpp
  bindings/serializable.cpp
  bindings/tokenizer.cpp
  wrappers/AbstractSerializableWrapper.cpp
  wrappers/AbstractSerializableWrapper.hpp
  wrappers/AbstractTokenizerWrapper.cpp
  wrappers/AbstractTokenizerWrapper.hpp
)

set_target_properties(bind-wasm PROPERTIES
  OUTPUT_NAME "kusai"
)

target_include_directories(bind-wasm PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(bind-wasm
  PRIVATE
    graph
    markov
    tokenizer
    textchain
    serializable
)

target_link_options(bind-wasm PRIVATE
  "--bind"
  "-sMODULARIZE=1"
)

install(TARGETS bind-wasm
  DESTINATION .
)
