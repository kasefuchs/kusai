kusai_add_library(
  NAME markov
  SRCS
    AbstractMarkov.cpp
    BackoffMarkov.cpp
    Markov.cpp
    NGramMarkov.cpp
  HDRS
    AbstractMarkov.hpp
    BackoffMarkov.hpp
    Markov.hpp
    NGramMarkov.hpp
  DEPS
    proto
    graph
    absl::log_internal_check_op
    xxHash::xxhash
)
