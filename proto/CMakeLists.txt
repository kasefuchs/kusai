kusai_add_library(
  NAME proto
  SRCS
    graph.proto
    markov.proto
    textchain.proto
    tokenizer.proto
  DEPS
    absl::status
    protobuf::libprotobuf
)

protobuf_generate(
  LANGUAGE cpp
  TARGET proto
  PROTOC_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/kusai/proto"
)

target_include_directories(proto PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  $<INSTALL_INTERFACE:include>
)
