add_library(markov
  Markov.cpp
  Markov.hpp
  NGramMarkov.cpp
  NGramMarkov.hpp
)

target_include_directories(markov
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  PUBLIC ${XXHASH_INCLUDE_DIRS}
)

target_link_libraries(markov
  PUBLIC proto
  PUBLIC graph
  PUBLIC ${XXHASH_LIBRARIES}
)
