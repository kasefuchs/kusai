#include "PyAbstractMarkov.hpp"

namespace kusai::bind::python {
nlohmann::json PyAbstractMarkov::serialize() const {
  PYBIND11_OVERRIDE_PURE(nlohmann::json, AbstractMarkov, serialize);
}

bool PyAbstractMarkov::deserialize(const nlohmann::json& data) {
  PYBIND11_OVERRIDE_PURE(bool, AbstractMarkov, deserialize, data);
}

void PyAbstractMarkov::trainUnlocked(const std::vector<std::vector<NodeId>>& sequences) {
  PYBIND11_OVERRIDE_PURE_NAME(void, AbstractMarkov, "_train_unlocked", trainUnlocked, sequences);
}

std::optional<NodeId> PyAbstractMarkov::nextNodeUnlocked(const std::vector<NodeId>& context) const {
  PYBIND11_OVERRIDE_PURE_NAME(std::optional<NodeId>, AbstractMarkov, "_next_node_unlocked", nextNodeUnlocked, context);
}
}  // namespace kusai::bind::python
