// Copyright (c) Kasefuchs
// SPDX-License-Identifier: MIT

#include "IdGenerator.hpp"
#include "idgen.pb.h"

uint32_t IdGenerator::next() {
  return ++lastId_;
}

uint32_t IdGenerator::current() const {
  return lastId_;
}

void IdGenerator::reset(const uint32_t value = 0) {
  lastId_ = value;
}

void IdGenerator::serialize(idgen::IdGenerator &out) const {
  out.set_last_id(lastId_);
}

void IdGenerator::deserialize(const idgen::IdGenerator &in) {
  lastId_ = in.last_id();
}
