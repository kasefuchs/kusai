add_library(textchain SHARED
  TextChain.cpp
  TextChain.hpp
)

target_include_directories(textchain
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(textchain
  PUBLIC proto
  PUBLIC graph
  PUBLIC markov
  PUBLIC tokenizer
  PUBLIC absl::strings
  PUBLIC xxHash::xxhash
)
