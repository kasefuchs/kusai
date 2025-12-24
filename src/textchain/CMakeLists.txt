add_library(textchain
  TextChain.cpp
  TextChain.hpp
)

target_include_directories(textchain
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  PUBLIC ${XXHASH_INCLUDE_DIRS}
)

target_link_libraries(textchain
  PUBLIC proto
  PUBLIC graph
  PUBLIC markov
  PUBLIC ${XXHASH_LIBRARIES}
)
