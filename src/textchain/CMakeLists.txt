add_library(textchain SHARED)

target_sources(textchain
  PRIVATE
    TextChain.cpp
  PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${CMAKE_SOURCE_DIR}/include
  FILES
    ${CMAKE_SOURCE_DIR}/include/kusai/textchain/TextChain.hpp
)

target_include_directories(textchain
  PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/kusai>
)

target_link_libraries(textchain
  PUBLIC proto
  PUBLIC graph
  PUBLIC markov
  PUBLIC tokenizer
  PUBLIC absl::strings
  PUBLIC xxHash::xxhash
)
