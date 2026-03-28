kusai_add_library(
  NAME serializable
  SRCS
    AbstractSerializable.cpp
  HDRS
    AbstractSerializable.hpp
  DEPS
    nlohmann_json::nlohmann_json
)
