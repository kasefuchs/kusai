add_executable(textchain_train
  main.cpp
)

target_include_directories(textchain_train
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(textchain_train
  PRIVATE textchain
  PRIVATE CLI11::CLI11
)
