#pragma once

#include <CLI/CLI.hpp>
#include <memory>

#include "kusai/markov/AbstractMarkov.hpp"
#include "kusai/markov/BackoffMarkov.hpp"
#include "kusai/markov/Markov.hpp"
#include "kusai/markov/NGramMarkov.hpp"

enum class ModelType { Markov, NGram, Backoff };

inline CLI::CheckedTransformer modelTypeTransformer() {
  static const std::map<std::string, ModelType> mapping = {
      {"markov", ModelType::Markov}, {"ngram", ModelType::NGram}, {"backoff", ModelType::Backoff}};

  return CLI::CheckedTransformer(mapping, CLI::ignore_case);
}

inline std::unique_ptr<AbstractMarkov> makeModel(const ModelType type, AbstractGraph& graph, int contextSize = 1) {
  switch (type) {
    case ModelType::Markov:
      return std::make_unique<Markov>(graph);

    case ModelType::NGram:
      return std::make_unique<NGramMarkov>(graph, contextSize);

    case ModelType::Backoff:
      return std::make_unique<BackoffMarkov>(graph, contextSize);
  }

  throw std::logic_error("Unknown model type");
}
