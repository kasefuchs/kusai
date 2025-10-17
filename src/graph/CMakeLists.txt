# Copyright (c) Kasefuchs
# SPDX-License-Identifier: MIT

add_library(graph
  Edge.cpp
  Edge.hpp
  Graph.cpp
  Graph.hpp
  Node.cpp
  Node.hpp
)

target_include_directories(graph
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(graph
  PRIVATE proto
)
