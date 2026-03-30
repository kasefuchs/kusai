#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// ReSharper disable once CppUnusedIncludeDirective
#include <pybind11_json/pybind11_json.hpp>

#include "kusai/serializable/AbstractSerializable.hpp"

namespace kusai::bind::python {
class PyAbstractSerializable : public AbstractSerializable {
 public:
  [[nodiscard]] nlohmann::json serialize() const override;
  bool deserialize(const nlohmann::json& data) override;
};
}  // namespace kusai::bind::python
