#include "Markov.hpp"

#include <google/protobuf/any.pb.h>

#include <optional>
#include <random>
#include <vector>

#include "AbstractGraph.hpp"
#include "graph.pb.h"
#include "markov.pb.h"

void Markov::train(const std::vector<std::vector<NodeId>>& sequences) {
  for (auto& seq : sequences) {
    NodeId prev = 0;
    for (const auto node : seq) {
      if (prev) {
        graph.modifyEdge(graph.ensureEdge(prev, node), [](graph::Edge& edge) { edge.set_weight(edge.weight() + 1); });
      }

      prev = node;
    }
  }
}

std::optional<NodeId> Markov::nextNode(const NodeId current) const {
  const auto outgoing = graph.getOutgoingEdges(current);
  if (outgoing.empty()) return std::nullopt;

  std::vector<double> weights;
  weights.reserve(outgoing.size());
  for (const auto& edge : outgoing) {
    weights.push_back(edge.weight());
  }

  std::discrete_distribution dist(weights.begin(), weights.end());
  const auto& chosen = outgoing[dist(rng_)];

  return chosen.target();
}

std::optional<NodeId> Markov::nextNode(const std::vector<NodeId>& context) const {
  const auto current = context.back();

  return nextNode(current);
}

void Markov::serialize(google::protobuf::Any& out) const {
  markov::Markov container;

  graph.serialize(*container.mutable_graph());

  out.PackFrom(container);
}

void Markov::deserialize(const google::protobuf::Any& in) {
  markov::Markov container;
  in.UnpackTo(&container);

  graph.deserialize(container.graph());
}
