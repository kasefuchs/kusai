add_library(graph SHARED
  Graph.cpp
  Graph.hpp
)

target_include_directories(graph
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(graph
  PUBLIC proto
  PRIVATE absl::numeric
  PRIVATE absl::flat_hash_map
  PRIVATE pugixml::pugixml
)
