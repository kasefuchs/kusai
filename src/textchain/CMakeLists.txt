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
    nlohmann_json::nlohmann_json
)
