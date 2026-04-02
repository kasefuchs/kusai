cmake_minimum_required(VERSION 3.16)

project(kusai
  VERSION 0.11.1
  LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(Settings)
include(Dependencies)
include(Helpers)

if (KUSAI_BUILD_APP)
  add_subdirectory(app)
endif ()

add_subdirectory(src)
add_subdirectory(bind)

if (KUSAI_INSTALL)
  include(Install)
endif ()
