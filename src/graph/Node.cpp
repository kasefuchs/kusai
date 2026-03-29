#include "kusai/graph/Node.hpp"

#include <string>

namespace kusai {
nlohmann::json Node::serialize() const { return {{"id", id}}; }

bool Node::deserialize(const nlohmann::json& data) {
  try {
    data.at("id").get_to(id);
  } catch (const nlohmann::json::exception&) {
    return false;
  }

  return true;
}
}  // namespace kusai
