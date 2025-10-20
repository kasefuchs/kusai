# Copyright (c) Kasefuchs
# SPDX-License-Identifier: MIT

add_library(proto SHARED
  graph.hpp
  graph.proto
  markov.hpp
  markov.proto
  textchain.proto
)

protobuf_generate(
  LANGUAGE cpp
  TARGET proto
)

target_include_directories(proto
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
