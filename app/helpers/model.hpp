#pragma once

#include <CLI/CLI.hpp>
#include <memory>

#include "kusai/markov/AbstractMarkov.hpp"
#include "kusai/markov/BackoffMarkov.hpp"
#include "kusai/markov/NGramMarkov.hpp"
#include "kusai/markov/SimpleMarkov.hpp"

enum class ModelType { Simple, NGram, Backoff };

inline CLI::CheckedTransformer modelTypeTransformer() {
  static const std::map<std::string, ModelType> mapping = {
      {"simple", ModelType::Simple}, {"ngram", ModelType::NGram}, {"backoff", ModelType::Backoff}};

  return CLI::CheckedTransformer(mapping, CLI::ignore_case);
}

inline std::shared_ptr<kusai::AbstractMarkov> makeModel(const ModelType type,
                                                        const std::shared_ptr<kusai::AbstractGraph>& graph,
                                                        int contextSize = 1) {
  switch (type) {
    case ModelType::Simple:
      return std::make_shared<kusai::SimpleMarkov>(graph);

    case ModelType::NGram:
      return std::make_shared<kusai::NGramMarkov>(graph, contextSize);

    case ModelType::Backoff:
      return std::make_shared<kusai::BackoffMarkov>(graph, contextSize);
  }

  throw std::logic_error("Unknown model type");
}
