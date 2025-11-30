add_library(markov
  Markov.cpp
  Markov.hpp
)

target_include_directories(markov
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

TARGET_LINK_LIBRARIES(markov
  PRIVATE proto
  PRIVATE graph
  PRIVATE idgen
)
