kusai_add_library(
  NAME common
  SRCS
    AbstractSerializable.cpp
  HDRS
    AbstractSerializable.hpp
  DEPS
    pugixml::pugixml
)
