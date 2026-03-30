#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// ReSharper disable once CppUnusedIncludeDirective
#include <pybind11_json/pybind11_json.hpp>

#include "kusai/markov/AbstractMarkov.hpp"

namespace kusai::bind::python {
class PyAbstractMarkov : public AbstractMarkov {
 public:
  explicit PyAbstractMarkov(const std::shared_ptr<AbstractGraph>& graph) : AbstractMarkov(graph) {}

  [[nodiscard]] nlohmann::json serialize() const override;
  bool deserialize(const nlohmann::json& data) override;

 protected:
  void trainUnlocked(const std::vector<std::vector<NodeId>>& sequences) override;

  std::optional<NodeId> nextNodeUnlocked(const std::vector<NodeId>& context) const override;
};
}  // namespace kusai::bind::python
