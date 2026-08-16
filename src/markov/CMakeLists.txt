kusai_add_library(
  NAME markov
  SRCS
    AbstractMarkov.cpp
    BackoffMarkov.cpp
    SimpleMarkov.cpp
    NGramMarkov.cpp
  HDRS
    AbstractMarkov.hpp
    BackoffMarkov.hpp
    SimpleMarkov.hpp
    NGramMarkov.hpp
  DEPS
    graph
    serializable
    nlohmann_json::nlohmann_json
    PkgConfig::libxxhash
)
