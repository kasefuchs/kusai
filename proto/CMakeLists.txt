add_library(proto STATIC
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
  PUBLIC absl::status
  PUBLIC absl::strings
  PUBLIC absl::numeric
  PUBLIC pugixml::pugixml
  PUBLIC protobuf::libprotobuf
)

target_include_directories(proto
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
