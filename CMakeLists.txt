cmake_minimum_required(VERSION 3.16)

project(kusai
  VERSION 0.3.3
  LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

include(Settings)
include(Dependencies)

if (KUSAI_BUILD_APP)
  add_subdirectory(app)
endif ()

add_subdirectory(proto)
add_subdirectory(src)

include(Install)
