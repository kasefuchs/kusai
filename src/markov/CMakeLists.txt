add_library(markov SHARED
  AbstractMarkov.hpp
  AbstractMarkov.cpp
  BackoffMarkov.cpp
  BackoffMarkov.hpp
  Markov.cpp
  Markov.hpp
  NGramMarkov.cpp
  NGramMarkov.hpp
)

target_include_directories(markov
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(markov
  PUBLIC proto
  PUBLIC graph
  PUBLIC xxHash::xxhash
)
