add_library(textchain
  TextChain.cpp
  TextChain.hpp
)

target_include_directories(textchain
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(textchain
  PRIVATE proto
  PRIVATE graph
  PRIVATE markov
  PRIVATE idgen
)
