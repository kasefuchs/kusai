cmake_minimum_required(VERSION 3.16)

project(kusai
  VERSION 0.3.1
  LANGUAGES CXX
)

include(Settings.cmake)
include(Dependencies.cmake)

if (KUSAI_BUILD_APP)
  add_subdirectory(app)
endif ()

add_subdirectory(proto)
add_subdirectory(src)

include(Install.cmake)
