add_library(proto SHARED
  graph.proto
  markov.proto
  textchain.proto
  tokenizer.proto
)

protobuf_generate(
  LANGUAGE cpp
  TARGET proto
)

target_link_libraries(proto
  PUBLIC protobuf::libprotobuf
  PUBLIC absl::status
)

target_include_directories(proto
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
