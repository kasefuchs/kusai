#pragma once

#include <cstdint>

#include "idgen.pb.h"

class IdGenerator {
public:
  IdGenerator() = default;

  ~IdGenerator() = default;

  uint32_t next();

  [[nodiscard]] uint32_t current() const;

  void reset(uint32_t value);

  void serialize(idgen::IdGenerator &out) const;

  void deserialize(const idgen::IdGenerator &in);

private:
  uint32_t lastId_ = 0;
};
