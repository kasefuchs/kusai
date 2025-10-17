# Copyright (c) Kasefuchs
# SPDX-License-Identifier: MIT

add_executable(${PROJECT_NAME}
  main.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
  PRIVATE proto
  PRIVATE graph
  PRIVATE absl::status
  PRIVATE absl::log_internal_check_op
  PRIVATE protobuf::libprotobuf
)
