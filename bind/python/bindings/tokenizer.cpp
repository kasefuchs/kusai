#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "bindings.hpp"
#include "kusai/serializable/AbstractSerializable.hpp"
#include "kusai/tokenizer/AbstractTokenizer.hpp"
#include "kusai/tokenizer/SimpleTokenizer.hpp"
#include "trampolines/PyAbstractTokenizer.hpp"

namespace py = pybind11;
namespace kusai::bind::python {
void bind_tokenizer(const py::module_& module) {
  py::class_<AbstractTokenizer, PyAbstractTokenizer, AbstractSerializable, std::shared_ptr<AbstractTokenizer> >(
      module, "AbstractTokenizer")
      .def(py::init<>())
      .def("encode", &AbstractTokenizer::encode)
      .def("decode", &AbstractTokenizer::decode);

  py::class_<SimpleTokenizer, AbstractTokenizer, std::shared_ptr<SimpleTokenizer> >(module, "SimpleTokenizer")
      .def(py::init<>());
}
}  // namespace kusai::bind::python
