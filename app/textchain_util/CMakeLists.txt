add_executable(textchain_util
  main.cpp
)

target_include_directories(textchain_util
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(textchain_util
  PRIVATE textchain
  PRIVATE CLI11::CLI11
)
