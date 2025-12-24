add_library(graph
  Graph.cpp
  Graph.hpp
)

target_include_directories(graph
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(graph
  PUBLIC proto
  PUBLIC absl::status
  PUBLIC absl::numeric
  PUBLIC absl::flat_hash_map
  PUBLIC absl::log_internal_check_op
)
