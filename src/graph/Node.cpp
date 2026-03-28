#include "kusai/graph/Node.hpp"

#include <string>

namespace kusai {
nlohmann::json Node::serialize() const { return {{"id", id}}; }

void Node::deserialize(const nlohmann::json& data) { data.at("id").get_to(id); }
}  // namespace kusai
