cmake_minimum_required(VERSION 3.16)

project(kusai
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include
include(FindProtobuf)

# Abseil
find_package(absl REQUIRED)

# Protobuf
find_package(Protobuf REQUIRED)

add_subdirectory(app)
add_subdirectory(proto)
add_subdirectory(src)
