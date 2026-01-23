add_library(proto SHARED
  graph.proto
  markov.proto
  textchain.proto
)

if (KUSAI_BUILD_SERVICE)
  target_sources(proto PRIVATE service.proto)
  protobuf_generate(
    LANGUAGE grpc
    TARGET proto
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
  )

  target_link_libraries(proto PUBLIC gRPC::grpc++)
endif ()

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
