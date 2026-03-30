#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// ReSharper disable once CppUnusedIncludeDirective
#include <pybind11_json/pybind11_json.hpp>

#include "kusai/tokenizer/AbstractTokenizer.hpp"

namespace kusai::bind::python {
class PyAbstractTokenizer : public AbstractTokenizer {
 public:
  [[nodiscard]] nlohmann::json serialize() const override;
  bool deserialize(const nlohmann::json& data) override;

 protected:
  std::vector<TokenId> encodeUnlocked(const std::string& text) override;
  std::string decodeUnlocked(const std::vector<TokenId>& text) override;
};
}  // namespace kusai::bind::python
