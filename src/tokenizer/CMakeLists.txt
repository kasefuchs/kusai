add_library(tokenizer
  AbstractTokenizer.cpp
  SimpleTokenizer.cpp
)

target_sources(tokenizer
  PUBLIC
    FILE_SET HEADERS
      TYPE HEADERS
      BASE_DIRS ${CMAKE_SOURCE_DIR}/include
      FILES
        ${CMAKE_SOURCE_DIR}/include/kusai/tokenizer/AbstractTokenizer.hpp
        ${CMAKE_SOURCE_DIR}/include/kusai/tokenizer/SimpleTokenizer.hpp
)

target_include_directories(tokenizer
  PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  PUBLIC $<INSTALL_INTERFACE:include>
)

target_link_libraries(tokenizer
  PUBLIC proto
  PUBLIC absl::strings
  PUBLIC absl::flat_hash_map
  PUBLIC xxHash::xxhash
)
