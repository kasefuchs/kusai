cmake_minimum_required(VERSION 3.16)

project(kusai
  VERSION 0.5.0
  LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

include(Settings)
include(Dependencies)
include(Helpers)

if (KUSAI_BUILD_APP)
  add_subdirectory(app)
endif ()

add_subdirectory(src)

include(Install)
