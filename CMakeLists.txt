cmake_minimum_required(VERSION 3.16)

project(kusai
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include
include(FindProtobuf)

# Protobuf
find_package(Protobuf REQUIRED)

# Abseil
find_package(absl REQUIRED)

# pugixml
find_package(pugixml REQUIRED)

# PkgConfig
find_package(PkgConfig REQUIRED)

# xxHash
pkg_check_modules(XXHASH REQUIRED libxxhash)

add_subdirectory(app)
add_subdirectory(proto)
add_subdirectory(src)
