kusai_add_library(
  NAME textchain
  SRCS
    TextChain.cpp
  HDRS
    TextChain.hpp
  DEPS
    proto
    graph
    markov
    tokenizer
    absl::strings
    xxHash::xxhash
)
