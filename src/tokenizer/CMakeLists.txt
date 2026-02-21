kusai_add_library(
  NAME tokenizer
  SRCS
  SimpleTokenizer.cpp
  HDRS
  AbstractTokenizer.hpp
  SimpleTokenizer.hpp
  DEPS
  common
  absl::strings
  absl::flat_hash_map
  pugixml::pugixml
  xxHash::xxhash
)
