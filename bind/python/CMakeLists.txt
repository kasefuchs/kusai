pybind11_add_module(bind-python
  module.cpp
  bindings.hpp
  bindings/graph.cpp
  bindings/markov.cpp
  bindings/tokenizer.cpp
  bindings/textchain.cpp
  bindings/serializable.cpp
  trampolines/PyAbstractGraph.cpp
  trampolines/PyAbstractGraph.hpp
  trampolines/PyAbstractMarkov.cpp
  trampolines/PyAbstractMarkov.hpp
  trampolines/PyAbstractTokenizer.cpp
  trampolines/PyAbstractTokenizer.hpp
  trampolines/PyAbstractSerializable.cpp
  trampolines/PyAbstractSerializable.hpp
)

set_target_properties(bind-python PROPERTIES
  OUTPUT_NAME "kusai"
)

target_include_directories(bind-python PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}
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

install(TARGETS bind-python
  DESTINATION .
)
