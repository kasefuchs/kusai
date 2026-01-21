add_library(proto SHARED
  graph.proto
  markov.proto
  service.proto
  textchain.proto
  helpers/graph.hpp
)

protobuf_generate(
  LANGUAGE cpp
  TARGET proto
)

protobuf_generate(
  LANGUAGE grpc
  TARGET proto
  GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
  PLUGIN "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
)

target_link_libraries(proto
  PUBLIC protobuf::libprotobuf
  PUBLIC gRPC::grpc++
  PRIVATE absl::status
  PRIVATE absl::strings
  PRIVATE absl::numeric
  PRIVATE pugixml::pugixml
)

target_include_directories(proto
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS proto
  LIBRARY DESTINATION lib
)
