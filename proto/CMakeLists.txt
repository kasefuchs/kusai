add_library(proto SHARED
  graph.proto
  markov.proto
  textchain.proto
  helpers/graph.hpp
)

protobuf_generate(
  LANGUAGE cpp
  TARGET proto
)

target_link_libraries(proto
  PUBLIC protobuf::libprotobuf
  PRIVATE absl::status
  PRIVATE absl::strings
  PRIVATE absl::numeric
  PRIVATE pugixml::pugixml
)

target_include_directories(proto
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
