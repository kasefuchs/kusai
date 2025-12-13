#include "IdGenerator.hpp"
#include "idgen.pb.h"

uint32_t IdGenerator::next() {
  return ++last_;
}

uint32_t IdGenerator::current() const {
  return last_;
}

void IdGenerator::reset(const uint32_t value = 0) {
  last_ = value;
}

void IdGenerator::serialize(idgen::IdGenerator &out) const {
  out.set_last(last_);
}

void IdGenerator::deserialize(const idgen::IdGenerator &in) {
  last_ = in.last();
}
