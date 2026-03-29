#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <iostream>
#include <pybind11_json/pybind11_json.hpp>

#include "kusai/graph/Edge.hpp"
#include "kusai/graph/MemoryGraph.hpp"
#include "kusai/markov/BackoffMarkov.hpp"
#include "kusai/markov/NGramMarkov.hpp"
#include "kusai/serializable/AbstractSerializable.hpp"
#include "kusai/textchain/TextChain.hpp"
#include "kusai/tokenizer/AbstractTokenizer.hpp"
#include "kusai/tokenizer/SimpleTokenizer.hpp"

namespace kusai {
class PyAbstractSerializable : public AbstractSerializable {
 public:
  [[nodiscard]] nlohmann::json serialize() const override {
    PYBIND11_OVERRIDE_PURE(nlohmann::json, AbstractSerializable, serialize);
  }

  bool deserialize(const nlohmann::json& data) override {
    PYBIND11_OVERRIDE_PURE(bool, AbstractSerializable, deserialize, data);
  }
};

class PyAbstractGraph : public AbstractGraph {
 public:
  [[nodiscard]] nlohmann::json serialize() const override {
    PYBIND11_OVERRIDE(nlohmann::json, AbstractGraph, serialize);
  }

  bool deserialize(const nlohmann::json& data) override { PYBIND11_OVERRIDE(bool, AbstractGraph, deserialize, data); }

  bool hasNodeUnlocked(NodeId id) const override {
    PYBIND11_OVERRIDE_PURE_NAME(bool, AbstractGraph, "_has_node_unlocked", hasNodeUnlocked, id);
  }

  bool hasEdgeUnlocked(EdgeId id) const override {
    PYBIND11_OVERRIDE_PURE_NAME(bool, AbstractGraph, "_has_edge_unlocked", hasEdgeUnlocked, id);
  }

  NodeId addNodeUnlocked(NodeId id, const std::function<void(Node&)>& fn) override {
    PYBIND11_OVERRIDE_PURE_NAME(NodeId, AbstractGraph, "_add_node_unlocked", addNodeUnlocked, id, fn);
  }

  EdgeId addEdgeUnlocked(NodeId source, NodeId target, const std::function<void(Edge&)>& fn) override {
    PYBIND11_OVERRIDE_PURE_NAME(EdgeId, AbstractGraph, "_add_edge_unlocked", addEdgeUnlocked, source, target, fn);
  }

  std::optional<Node> getNodeUnlocked(NodeId id) const override {
    PYBIND11_OVERRIDE_PURE_NAME(std::optional<Node>, AbstractGraph, "_get_node_unlocked", getNodeUnlocked, id);
  }

  std::optional<Edge> getEdgeUnlocked(EdgeId id) const override {
    PYBIND11_OVERRIDE_PURE_NAME(std::optional<Edge>, AbstractGraph, "_get_edge_unlocked", getEdgeUnlocked, id);
  }

  bool modifyNodeUnlocked(NodeId id, std::function<void(Node&)> fn) override {
    PYBIND11_OVERRIDE_PURE_NAME(bool, AbstractGraph, "_modify_node_unlocked", modifyNodeUnlocked, id, fn);
  }

  bool modifyEdgeUnlocked(EdgeId id, std::function<void(Edge&)> fn) override {
    PYBIND11_OVERRIDE_PURE_NAME(bool, AbstractGraph, "_modify_edge_unlocked", modifyEdgeUnlocked, id, fn);
  }

  std::vector<NodeId> getAllNodeIdsUnlocked() const override {
    PYBIND11_OVERRIDE_PURE_NAME(std::vector<NodeId>, AbstractGraph, "_get_all_node_ids_unlocked",
                                getAllNodeIdsUnlocked);
  }

  std::vector<EdgeId> getAllEdgeIdsUnlocked() const override {
    PYBIND11_OVERRIDE_PURE_NAME(std::vector<EdgeId>, AbstractGraph, "_get_all_edge_ids_unlocked",
                                getAllEdgeIdsUnlocked);
  }

  std::vector<EdgeId> getIncomingEdgeIdsUnlocked(NodeId target) const override {
    PYBIND11_OVERRIDE_PURE_NAME(std::vector<EdgeId>, AbstractGraph, "_get_incoming_edge_ids_unlocked",
                                getIncomingEdgeIdsUnlocked, target);
  }

  std::vector<EdgeId> getOutgoingEdgeIdsUnlocked(NodeId source) const override {
    PYBIND11_OVERRIDE_PURE_NAME(std::vector<EdgeId>, AbstractGraph, "_get_outgoing_edge_ids_unlocked",
                                getOutgoingEdgeIdsUnlocked, source);
  }

  std::vector<Node> getAllNodesUnlocked() const override {
    PYBIND11_OVERRIDE_PURE_NAME(std::vector<Node>, AbstractGraph, "_get_all_nodes_unlocked", getAllNodesUnlocked);
  }

  std::vector<Edge> getAllEdgesUnlocked() const override {
    PYBIND11_OVERRIDE_PURE_NAME(std::vector<Edge>, AbstractGraph, "_get_all_edges_unlocked", getAllEdgesUnlocked);
  }

  std::vector<Edge> getIncomingEdgesUnlocked(NodeId target) const override {
    PYBIND11_OVERRIDE_PURE_NAME(std::vector<Edge>, AbstractGraph, "_get_incoming_edges_unlocked",
                                getIncomingEdgesUnlocked, target);
  }

  std::vector<Edge> getOutgoingEdgesUnlocked(NodeId source) const override {
    PYBIND11_OVERRIDE_PURE_NAME(std::vector<Edge>, AbstractGraph, "_get_outgoing_edges_unlocked",
                                getOutgoingEdgesUnlocked, source);
  }

  void clearNodesUnlocked() override {
    PYBIND11_OVERRIDE_PURE_NAME(void, AbstractGraph, "_clear_nodes_unlocked", clearNodesUnlocked);
  }

  void clearEdgesUnlocked() override {
    PYBIND11_OVERRIDE_PURE_NAME(void, AbstractGraph, "_clear_edges_unlocked", clearEdgesUnlocked);
  }
};

class PyAbstractTokenizer : public AbstractTokenizer {
 public:
  [[nodiscard]] nlohmann::json serialize() const override {
    PYBIND11_OVERRIDE_PURE(nlohmann::json, AbstractTokenizer, serialize);
  }

  bool deserialize(const nlohmann::json& data) override {
    PYBIND11_OVERRIDE_PURE(bool, AbstractTokenizer, deserialize, data);
  }

 protected:
  std::vector<TokenId> encodeUnlocked(const std::string& text) override {
    PYBIND11_OVERRIDE_PURE_NAME(std::vector<TokenId>, AbstractTokenizer, "_encode_unlocked", encodeUnlocked, text);
  }

  std::string decodeUnlocked(const std::vector<TokenId>& text) override {
    PYBIND11_OVERRIDE_PURE_NAME(std::string, AbstractTokenizer, "_decode_unlocked", decodeUnlocked, text);
  }
};

class PyAbstractMarkov : public AbstractMarkov {
 public:
  explicit PyAbstractMarkov(const std::shared_ptr<AbstractGraph>& graph) : AbstractMarkov(graph) {}

  [[nodiscard]] nlohmann::json serialize() const override {
    PYBIND11_OVERRIDE_PURE(nlohmann::json, AbstractMarkov, serialize);
  }

  bool deserialize(const nlohmann::json& data) override {
    PYBIND11_OVERRIDE_PURE(bool, AbstractMarkov, deserialize, data);
  }

 protected:
  void trainUnlocked(const std::vector<std::vector<NodeId>>& sequences) override {
    PYBIND11_OVERRIDE_PURE_NAME(void, AbstractMarkov, "_train_unlocked", trainUnlocked, sequences);
  }

  std::optional<NodeId> nextNodeUnlocked(const std::vector<NodeId>& context) const override {
    PYBIND11_OVERRIDE_PURE_NAME(std::optional<NodeId>, AbstractMarkov, "_next_node_unlocked", nextNodeUnlocked,
                                context);
  }
};

namespace py = pybind11;

PYBIND11_MODULE(kusai, m) {
  py::class_<AbstractSerializable, PyAbstractSerializable, std::shared_ptr<AbstractSerializable>>(
      m, "AbstractSerializable")
      .def(py::init())
      .def("serialize", &AbstractSerializable::serialize)
      .def("deserialize", &AbstractSerializable::deserialize);

  py::class_<Node, AbstractSerializable, std::shared_ptr<Node>>(m, "Node")
      .def(py::init<>())
      .def_readwrite("id", &Node::id);

  py::class_<Edge, AbstractSerializable, std::shared_ptr<Edge>>(m, "Edge")
      .def(py::init<>())
      .def_static("make_id", &Edge::makeId)
      .def_readwrite("source", &Edge::source)
      .def_readwrite("target", &Edge::target)
      .def_readwrite("weight", &Edge::weight);

  py::class_<AbstractGraph, PyAbstractGraph, AbstractSerializable, std::shared_ptr<AbstractGraph>>(m, "AbstractGraph")
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

  py::class_<MemoryGraph, AbstractGraph, std::shared_ptr<MemoryGraph>>(m, "MemoryGraph").def(py::init<>());

  py::class_<AbstractMarkov, PyAbstractMarkov, AbstractSerializable, std::shared_ptr<AbstractMarkov>>(m,
                                                                                                      "AbstractMarkov")
      .def(py::init<const std::shared_ptr<AbstractGraph>&>(), py::arg("graph"))
      .def("train", &AbstractMarkov::train, py::arg("sequences"))
      .def("next_node", &AbstractMarkov::nextNode, py::arg("context"))
      .def("generate_sequence", &AbstractMarkov::generateSequence, py::arg("context"), py::arg("limit") = INT8_MAX)
      .def_readonly("graph", &AbstractMarkov::graph);

  py::class_<SimpleMarkov, AbstractMarkov, std::shared_ptr<SimpleMarkov>>(m, "SimpleMarkov")
      .def(py::init<const std::shared_ptr<AbstractGraph>&>(), py::arg("graph"));

  py::class_<NGramMarkov, SimpleMarkov, std::shared_ptr<NGramMarkov>>(m, "NGramMarkov")
      .def(py::init<const std::shared_ptr<AbstractGraph>&, uint32_t>(), py::arg("graph"), py::arg("context_size") = 1);

  py::class_<BackoffMarkov, AbstractMarkov, std::shared_ptr<BackoffMarkov>>(m, "BackoffMarkov")
      .def(py::init<const std::shared_ptr<AbstractGraph>&, uint32_t>(), py::arg("graph"),
           py::arg("max_context_size") = 1);

  py::class_<AbstractTokenizer, PyAbstractTokenizer, AbstractSerializable, std::shared_ptr<AbstractTokenizer>>(
      m, "AbstractTokenizer")
      .def(py::init<>())
      .def("encode", &AbstractTokenizer::encode)
      .def("decode", &AbstractTokenizer::decode);

  py::class_<SimpleTokenizer, AbstractTokenizer, std::shared_ptr<SimpleTokenizer>>(m, "SimpleTokenizer")
      .def(py::init<>());

  py::class_<TextChain, AbstractSerializable, std::shared_ptr<TextChain>>(m, "TextChain")
      .def(py::init<const std::shared_ptr<AbstractMarkov>&, const std::shared_ptr<AbstractTokenizer>&>(),
           py::arg("markov"), py::arg("tokenizer"))
      .def("train", &TextChain::train, py::arg("sequences"))
      .def("generate_sequence", &TextChain::generateSequence, py::arg("context"), py::arg("limit") = INT8_MAX)
      .def("generate_text", &TextChain::generateText, py::arg("context"), py::arg("limit") = INT8_MAX)
      .def_readonly("markov", &TextChain::markov)
      .def_readonly("tokenizer", &TextChain::tokenizer);
}

}  // namespace kusai
