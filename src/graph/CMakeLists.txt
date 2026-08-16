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
    nlohmann_json::nlohmann_json
    PkgConfig::libxxhash
)
