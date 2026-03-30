#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "bindings.hpp"
#include "kusai/markov/AbstractMarkov.hpp"
#include "kusai/markov/BackoffMarkov.hpp"
#include "kusai/markov/NGramMarkov.hpp"
#include "kusai/markov/SimpleMarkov.hpp"
#include "kusai/serializable/AbstractSerializable.hpp"
#include "trampolines/PyAbstractMarkov.hpp"

namespace py = pybind11;
namespace kusai::bind::python {
void bind_markov(const py::module_& module) {
  py::class_<AbstractMarkov, PyAbstractMarkov, AbstractSerializable, std::shared_ptr<AbstractMarkov> >(module,
                                                                                                       "AbstractMarkov")
      .def(py::init<const std::shared_ptr<AbstractGraph>&>(), py::arg("graph"))
      .def("train", &AbstractMarkov::train, py::arg("sequences"))
      .def("next_node", &AbstractMarkov::nextNode, py::arg("context"))
      .def("generate_sequence", &AbstractMarkov::generateSequence, py::arg("context"), py::arg("limit") = INT8_MAX)
      .def_readonly("graph", &AbstractMarkov::graph);

  py::class_<SimpleMarkov, AbstractMarkov, std::shared_ptr<SimpleMarkov> >(module, "SimpleMarkov")
      .def(py::init<const std::shared_ptr<AbstractGraph>&>(), py::arg("graph"));

  py::class_<NGramMarkov, SimpleMarkov, std::shared_ptr<NGramMarkov> >(module, "NGramMarkov")
      .def(py::init<const std::shared_ptr<AbstractGraph>&, std::uint32_t>(), py::arg("graph"),
           py::arg("context_size") = 1);

  py::class_<BackoffMarkov, AbstractMarkov, std::shared_ptr<BackoffMarkov> >(module, "BackoffMarkov")
      .def(py::init<const std::shared_ptr<AbstractGraph>&, std::uint32_t>(), py::arg("graph"),
           py::arg("max_context_size") = 1);
}
}  // namespace kusai::bind::python
