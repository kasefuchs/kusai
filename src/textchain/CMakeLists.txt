kusai_add_library(
  NAME textchain
  SRCS
    TextChain.cpp
  HDRS
    TextChain.hpp
  DEPS
    graph
    markov
    tokenizer
    serializable
    absl::strings
    nlohmann_json::nlohmann_json
)
