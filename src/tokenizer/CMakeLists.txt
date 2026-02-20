kusai_add_library(
  NAME tokenizer
  SRCS
    AbstractTokenizer.cpp
    SimpleTokenizer.cpp
  HDRS
    AbstractTokenizer.hpp
    SimpleTokenizer.hpp
  DEPS
    proto
    absl::strings
    absl::flat_hash_map
    xxHash::xxhash
)
