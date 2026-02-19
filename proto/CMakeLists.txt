add_library(proto SHARED
  graph.proto
  markov.proto
  textchain.proto
  tokenizer.proto
)

protobuf_generate(
  LANGUAGE cpp
  TARGET proto
  PROTOC_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/kusai/proto"
)

target_link_libraries(proto
  PUBLIC protobuf::libprotobuf
  PUBLIC absl::status
)

target_include_directories(proto
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
