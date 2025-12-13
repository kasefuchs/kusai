add_library(textchain
  TextChain.cpp
  TextChain.hpp
)

target_include_directories(textchain
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

TARGET_LINK_LIBRARIES(textchain
  PRIVATE proto
  PRIVATE graph
  PRIVATE markov
  PRIVATE util
)
