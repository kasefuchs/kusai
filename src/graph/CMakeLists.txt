kusai_add_library(
  NAME graph
  SRCS
    AbstractGraph.cpp
    MemoryGraph.cpp
  HDRS
    AbstractGraph.hpp
    MemoryGraph.hpp
  DEPS
    proto
    absl::numeric
    absl::flat_hash_map
)
