cmake_minimum_required(VERSION 3.16)

project(kusai
  LANGUAGES CXX
)

include(Settings.cmake)
include(Dependencies.cmake)

add_subdirectory(app)
add_subdirectory(proto)
add_subdirectory(src)

include(Install.cmake)
