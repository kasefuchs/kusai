#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "bindings.hpp"
#include "kusai/serializable/AbstractSerializable.hpp"
#include "trampolines/PyAbstractSerializable.hpp"

namespace py = pybind11;
namespace kusai::bind::python {
void bind_serializable(const py::module_& module) {
  py::class_<AbstractSerializable, PyAbstractSerializable, std::shared_ptr<AbstractSerializable> >(
      module, "AbstractSerializable")
      .def(py::init())
      .def("serialize", &AbstractSerializable::serialize)
      .def("deserialize", &AbstractSerializable::deserialize);
}
}  // namespace kusai::bind::python
