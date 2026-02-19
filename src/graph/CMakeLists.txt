add_library(graph SHARED)

target_sources(graph
  PRIVATE
    AbstractGraph.cpp
    MemoryGraph.cpp
  PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${CMAKE_SOURCE_DIR}/include
  FILES
    ${CMAKE_SOURCE_DIR}/include/kusai/graph/AbstractGraph.hpp
    ${CMAKE_SOURCE_DIR}/include/kusai/graph/MemoryGraph.hpp
)

target_include_directories(graph
  PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/kusai>
)

target_link_libraries(graph
  PUBLIC proto
  PUBLIC absl::numeric
  PUBLIC absl::flat_hash_map
)
