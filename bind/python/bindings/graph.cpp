#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// ReSharper disable once CppUnusedIncludeDirective
#include <pybind11_json/pybind11_json.hpp>

#include "bindings.hpp"
#include "kusai/graph/AbstractGraph.hpp"
#include "kusai/graph/Edge.hpp"
#include "kusai/graph/MemoryGraph.hpp"
#include "kusai/graph/Node.hpp"
#include "kusai/serializable/AbstractSerializable.hpp"
#include "trampolines/PyAbstractGraph.hpp"

namespace py = pybind11;
namespace kusai::bind::python {
void bind_graph(const py::module_& module) {
  py::class_<Node, AbstractSerializable, std::shared_ptr<Node> >(module, "Node")
      .def(py::init<>())
      .def_readwrite("id", &Node::id);

  py::class_<Edge, AbstractSerializable, std::shared_ptr<Edge> >(module, "Edge")
      .def(py::init<>())
      .def_static("make_id", &Edge::makeId)
      .def_readwrite("source", &Edge::source)
      .def_readwrite("target", &Edge::target)
      .def_readwrite("weight", &Edge::weight);

  py::class_<AbstractGraph, PyAbstractGraph, AbstractSerializable, std::shared_ptr<AbstractGraph> >(module,
                                                                                                    "AbstractGraph")
      .def(py::init<>())
      .def("has_node", &AbstractGraph::hasNode)
      .def("has_edge", py::overload_cast<EdgeId>(&AbstractGraph::hasEdge, py::const_))
      .def("has_edge", py::overload_cast<NodeId, NodeId>(&AbstractGraph::hasEdge, py::const_))
      .def("add_node", &AbstractGraph::addNode)
      .def("add_edge", py::overload_cast<NodeId, NodeId, const std::function<void(Edge&)>&>(&AbstractGraph::addEdge))
      .def("ensure_node", &AbstractGraph::ensureNode)
      .def("ensure_edge", &AbstractGraph::ensureEdge)
      .def("get_node", &AbstractGraph::getNode)
      .def("get_edge", py::overload_cast<EdgeId>(&AbstractGraph::getEdge, py::const_))
      .def("get_edge", py::overload_cast<NodeId, NodeId>(&AbstractGraph::getEdge, py::const_))
      .def("modify_node", &AbstractGraph::modifyNode)
      .def("modify_edge", py::overload_cast<EdgeId, const std::function<void(Edge&)>&>(&AbstractGraph::modifyEdge))
      .def("modify_edge",
           py::overload_cast<NodeId, NodeId, const std::function<void(Edge&)>&>(&AbstractGraph::modifyEdge))
      .def("get_all_node_ids", &AbstractGraph::getAllNodeIds)
      .def("get_all_edge_ids", &AbstractGraph::getAllEdgeIds)
      .def("get_incoming_edge_ids", &AbstractGraph::getIncomingEdgeIds)
      .def("get_outgoing_edge_ids", &AbstractGraph::getOutgoingEdgeIds)
      .def("get_all_nodes", &AbstractGraph::getAllNodes)
      .def("get_all_edges", &AbstractGraph::getAllEdges)
      .def("get_incoming_edges", &AbstractGraph::getIncomingEdges)
      .def("get_outgoing_edges", &AbstractGraph::getOutgoingEdges)
      .def("clear_nodes", &AbstractGraph::clearNodes)
      .def("clear_edges", &AbstractGraph::clearEdges)
      .def("clear", &AbstractGraph::clear);

  py::class_<MemoryGraph, AbstractGraph, std::shared_ptr<MemoryGraph> >(module, "MemoryGraph").def(py::init<>());
}
}  // namespace kusai::bind::python
