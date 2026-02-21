kusai_add_library(
  NAME textchain
  SRCS
  TextChain.cpp
  HDRS
  TextChain.hpp
  DEPS
  common
  graph
  markov
  tokenizer
  absl::strings
  pugixml::pugixml
)
