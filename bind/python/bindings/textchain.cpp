#include "kusai/textchain/TextChain.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "bindings.hpp"
#include "kusai/markov/AbstractMarkov.hpp"
#include "kusai/serializable/AbstractSerializable.hpp"
#include "kusai/tokenizer/AbstractTokenizer.hpp"

namespace py = pybind11;
namespace kusai::bind::python {
void bind_textchain(const py::module_& module) {
  py::class_<TextChain, AbstractSerializable, std::shared_ptr<TextChain> >(module, "TextChain")
      .def(py::init<const std::shared_ptr<AbstractMarkov>&, const std::shared_ptr<AbstractTokenizer>&>(),
           py::arg("markov"), py::arg("tokenizer"))
      .def("train", &TextChain::train, py::arg("sequences"))
      .def("generate_sequence", &TextChain::generateSequence, py::arg("context"), py::arg("limit") = INT8_MAX)
      .def("generate_text", &TextChain::generateText, py::arg("context"), py::arg("limit") = INT8_MAX)
      .def_readonly("markov", &TextChain::markov)
      .def_readonly("tokenizer", &TextChain::tokenizer);
}
}  // namespace kusai::bind::python
