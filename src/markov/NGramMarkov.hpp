#pragma once
#include "Markov.hpp"
#include "markov.pb.h"

class NGramMarkov : public Markov {
public:
  explicit NGramMarkov(const uint32_t n) : n_(n) {
  }

  void train(const std::vector<std::vector<graph::Node *> > &sequences) override;

  graph::Node *nextNode(const std::vector<graph::Node *> &context) const override;

  void serialize(markov::NGramMarkov &out) const;

  void serializeToOstream(std::ostream &out) const override;

  void deserialize(const markov::NGramMarkov &in);

  void deserializeFromIstream(std::istream &in) override;

private:
  uint32_t n_;

  static uint64_t makeContextId(const std::vector<uint64_t> &ids);

protected:
  using Graph::nodes_;
  using Graph::edges_;
};
