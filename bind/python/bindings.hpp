#pragma once

#include <pybind11/pybind11.h>

namespace py = pybind11;
namespace kusai::bind::python {
void bind_graph(const py::module_& module);
void bind_markov(const py::module_& module);
void bind_tokenizer(const py::module_& module);
void bind_textchain(const py::module_& module);
void bind_serializable(const py::module_& module);
}  // namespace kusai::bind::python
