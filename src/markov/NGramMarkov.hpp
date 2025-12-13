#pragma once
#include "Markov.hpp"
#include "markov.pb.h"

class NGramMarkov : public Markov {
public:
  explicit NGramMarkov(const uint32_t n) : n_(n) {
  }

  void train(const std::vector<std::vector<graph::Node *> > &sequences);

  graph::Node *nextNode(const std::vector<graph::Node *> &context) const;

  void serialize(markov::NGramMarkov &out) const;

  void deserialize(const markov::NGramMarkov &in);

private:
  uint32_t n_;

  static uint32_t makeContextId(const std::vector<uint32_t> &ids);

protected:
  using Graph::nodes_;
  using Graph::edges_;
};
