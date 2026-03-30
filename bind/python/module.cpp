#include <pybind11/pybind11.h>

#include <iostream>

#include "bindings.hpp"

namespace py = pybind11;
namespace kusai::bind::python {
PYBIND11_MODULE(kusai, module) {
  bind_serializable(module);
  bind_graph(module);
  bind_markov(module);
  bind_tokenizer(module);
  bind_textchain(module);
}
}  // namespace kusai::bind::python
