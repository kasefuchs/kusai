add_executable(${PROJECT_NAME}
  main.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE textchain
  PRIVATE absl::status
  PRIVATE absl::log_internal_check_op
)
