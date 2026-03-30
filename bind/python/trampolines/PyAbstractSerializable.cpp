#include "PyAbstractSerializable.hpp"

namespace kusai::bind::python {
nlohmann::json PyAbstractSerializable::serialize() const {
  PYBIND11_OVERRIDE_PURE(nlohmann::json, AbstractSerializable, serialize);
}

bool PyAbstractSerializable::deserialize(const nlohmann::json& data) {
  PYBIND11_OVERRIDE_PURE(bool, AbstractSerializable, deserialize, data);
}
}  // namespace kusai::bind::python
