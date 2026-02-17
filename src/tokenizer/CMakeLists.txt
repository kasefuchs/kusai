add_library(tokenizer SHARED
  AbstractTokenizer.cpp
  AbstractTokenizer.hpp
  SimpleTokenizer.cpp
  SimpleTokenizer.hpp
)

target_include_directories(tokenizer
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(tokenizer
  PUBLIC proto
  PUBLIC absl::strings
  PUBLIC absl::flat_hash_map
  PUBLIC xxHash::xxhash
)
