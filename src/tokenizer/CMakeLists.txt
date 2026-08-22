kusai_add_library(
  NAME tokenizer
  SRCS
    AbstractTokenizer.cpp
    SimpleTokenizer.cpp
  HDRS
    AbstractTokenizer.hpp
    SimpleTokenizer.hpp
  DEPS
    serializable
    nlohmann_json::nlohmann_json
    xxHash::xxhash
)
