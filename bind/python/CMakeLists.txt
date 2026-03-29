pybind11_add_module(bind-python
  module.cpp
)

set_target_properties(bind-python PROPERTIES
  OUTPUT_NAME "kusai"
)

target_include_directories(bind-python PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(bind-python
  PRIVATE
    graph
    markov
    tokenizer
    textchain
    serializable
    pybind11_json
)
