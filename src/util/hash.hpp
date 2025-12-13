#pragma once
#include <cstdint>

namespace util::hash {
  inline uint32_t fnv1a(const char *data, const size_t len) {
    uint32_t hash = 0x811C9DC5;
    for (size_t i = 0; i < len; i++) {
      hash ^= data[i];
      hash *= 0x01000193;
    }

    return hash;
  }
}
