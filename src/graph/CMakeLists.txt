kusai_add_library(
  NAME graph
  SRCS
    Node.cpp
    Edge.cpp
    AbstractGraph.cpp
    MemoryGraph.cpp
  HDRS
    Node.hpp
    Edge.hpp
    AbstractGraph.hpp
    MemoryGraph.hpp
  DEPS
    serializable
    absl::flat_hash_map
    nlohmann_json::nlohmann_json
    xxHash::xxhash
)
