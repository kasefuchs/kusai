# Copyright (c) Kasefuchs
# SPDX-License-Identifier: MIT

add_library(proto SHARED
  graph.proto
)

protobuf_generate(
  LANGUAGE cpp
  TARGET proto
)

target_include_directories(proto
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
)
