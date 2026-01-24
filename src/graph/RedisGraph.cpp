#include "RedisGraph.hpp"

#include <absl/log/check.h>
#include <absl/strings/numbers.h>
#include <absl/strings/str_format.h>
#include <sw/redis++/utils.h>

#include <cstdint>
#include <functional>
#include <iterator>
#include <optional>
#include <ranges>
#include <utility>
#include <vector>

#include "AbstractGraph.hpp"
#include "graph.pb.h"

bool RedisGraph::hasNode(const NodeId id) {
  const auto key = makeNodeKey(id);

  return redis_.exists(key);
}

bool RedisGraph::hasEdge(const EdgeId id) {
  const auto key = makeEdgeKey(id);

  return redis_.exists(key);
}

NodeId RedisGraph::addNode(const NodeId id) {
  graph::Node node;
  node.set_id(id);

  const auto key = makeNodeKey(id);
  redis_.set(key, node.SerializeAsString());

  return id;
}

EdgeId RedisGraph::addEdge(const EdgeId id) {
  const auto [source, target] = splitEdgeId(id);

  graph::Edge edge;
  edge.set_source(source);
  edge.set_target(target);

  const auto key = makeEdgeKey(id);
  redis_.set(key, edge.SerializeAsString());

  return id;
}

std::optional<graph::Node> RedisGraph::getNode(const NodeId id) const {
  const auto key = makeNodeKey(id);
  if (auto val = redis_.get(key)) {
    graph::Node node;
    node.ParseFromString(*val);

    return node;
  }

  return std::nullopt;
}

std::optional<graph::Edge> RedisGraph::getEdge(const EdgeId id) const {
  const auto key = makeEdgeKey(id);
  if (auto val = redis_.get(key)) {
    graph::Edge edge;
    edge.ParseFromString(*val);

    return edge;
  }

  return std::nullopt;
}

bool RedisGraph::modifyNode(const NodeId id, const std::function<void(graph::Node&)> fn) {
  const auto key = makeNodeKey(id);
  if (auto node = getNode(id)) {
    fn(*node);

    return redis_.set(key, node->SerializeAsString());
  }

  return false;
}

bool RedisGraph::modifyEdge(const EdgeId id, const std::function<void(graph::Edge&)> fn) {
  const auto key = makeEdgeKey(id);
  if (auto edge = getEdge(id)) {
    fn(*edge);

    return redis_.set(key, edge->SerializeAsString());
  }

  return false;
}

std::vector<NodeId> RedisGraph::getAllNodeIds() const {
  const auto ids = getAllKeys("N:*") | std::views::transform([](const auto& e) { return parseNodeKey(e); });

  return {ids.begin(), ids.end()};
}

std::vector<EdgeId> RedisGraph::getAllEdgeIds() const {
  const auto ids = getAllKeys("E:*") | std::views::transform([](const auto& e) { return parseEdgeKey(e); });

  return {ids.begin(), ids.end()};
}

std::vector<EdgeId> RedisGraph::getIncomingEdgeIds(const NodeId target) const {
  const auto [_, pattern] = makeEdgePattern(target);
  const auto ids = getAllKeys(pattern) | std::views::transform([](const auto& e) { return parseEdgeKey(e); });

  return {ids.begin(), ids.end()};
}

std::vector<EdgeId> RedisGraph::getOutgoingEdgeIds(const NodeId source) const {
  const auto [pattern, _] = makeEdgePattern(source);
  const auto ids = getAllKeys(pattern) | std::views::transform([](const auto& e) { return parseEdgeKey(e); });

  return {ids.begin(), ids.end()};
}

std::vector<graph::Node> RedisGraph::getAllNodes() const {
  if (const auto keys = getAllKeys("N:*"); !keys.empty()) {
    return getNodesByKeys(keys);
  }

  return {};
}

std::vector<graph::Edge> RedisGraph::getAllEdges() const {
  if (const auto keys = getAllKeys("E:*"); !keys.empty()) {
    return getEdgesByKeys(keys);
  }

  return {};
}

std::vector<graph::Edge> RedisGraph::getIncomingEdges(const NodeId target) const {
  const auto [_, pattern] = makeEdgePattern(target);
  if (const auto keys = getAllKeys(pattern); !keys.empty()) {
    return getEdgesByKeys(keys);
  }

  return {};
}

std::vector<graph::Edge> RedisGraph::getOutgoingEdges(const NodeId source) const {
  const auto [pattern, _] = makeEdgePattern(source);
  if (const auto keys = getAllKeys(pattern); !keys.empty()) {
    return getEdgesByKeys(keys);
  }

  return {};
}

void RedisGraph::clearNodes() {
  if (const auto keys = getAllKeys("N:*"); !keys.empty()) {
    redis_.del(keys.begin(), keys.end());
  }
}

void RedisGraph::clearEdges() {
  if (const auto keys = getAllKeys("E:*"); !keys.empty()) {
    redis_.del(keys.begin(), keys.end());
  }
}

std::vector<std::string> RedisGraph::getAllKeys(const std::string& pattern) const {
  sw::redis::Cursor cursor = 0;
  std::vector<std::string> keys;

  do {
    cursor = redis_.scan(cursor, pattern, UINT32_MAX, std::back_inserter(keys));
    if (cursor == 0) {
      break;
    }
    // ReSharper disable once CppDFAConstantConditions
  } while (cursor != 0);

  return keys;
}

std::vector<graph::Node> RedisGraph::getNodesByKeys(const std::vector<std::string>& keys) const {
  std::vector<std::string> vals;
  vals.reserve(keys.size());
  redis_.mget(keys.begin(), keys.end(), std::back_inserter(vals));

  std::vector<graph::Node> result;
  result.reserve(vals.size());

  for (const auto& val : vals) {
    graph::Node node;
    node.ParseFromString(val);
    result.push_back(std::move(node));
  }

  return result;
}

std::vector<graph::Edge> RedisGraph::getEdgesByKeys(const std::vector<std::string>& keys) const {
  std::vector<std::string> vals;
  vals.reserve(keys.size());
  redis_.mget(keys.begin(), keys.end(), std::back_inserter(vals));

  std::vector<graph::Edge> result;
  result.reserve(vals.size());

  for (const auto& val : vals) {
    graph::Edge edge;
    edge.ParseFromString(val);
    result.push_back(std::move(edge));
  }

  return result;
}

std::string RedisGraph::makeNodeKey(const NodeId id) { return absl::StrFormat("N:%016X", id); }

std::string RedisGraph::makeEdgeKey(const EdgeId id) { return absl::StrFormat("E:%032X", id); }

std::pair<std::string, std::string> RedisGraph::makeEdgePattern(const NodeId id) {
  return {
      absl::StrFormat("E:%016X*", id),  // source known
      absl::StrFormat("E:*%016X", id),  // target known
  };
}

NodeId RedisGraph::parseNodeKey(const std::string& key) {
  NodeId id;

  const auto ok = absl::SimpleHexAtoi(key.substr(2), &id);
  CHECK(ok) << "Invalid node key: " << key;

  return id;
}

EdgeId RedisGraph::parseEdgeKey(const std::string& key) {
  EdgeId id;

  const auto ok = absl::SimpleHexAtoi(key.substr(2), &id);
  CHECK(ok) << "Invalid edge key: " << key;

  return id;
}
