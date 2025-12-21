add_library(proto SHARED
  graph.hpp
  graph.proto
  markov.proto
  textchain.proto
)

protobuf_generate(
  LANGUAGE cpp
  TARGET proto
)

target_link_libraries(proto
  PUBLIC protobuf::libprotobuf
)

target_include_directories(proto
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
