cmake_minimum_required(VERSION 4.1)

project(kusai
  VERSION 0.12.1
  LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(Settings)
include(Dependencies)
include(Helpers)

if (KUSAI_BUILD_APP)
  add_subdirectory(app)
endif ()

if (KUSAI_BUILD_DOC)
  add_subdirectory(doc)
endif ()

add_subdirectory(src)
add_subdirectory(bind)

if (KUSAI_INSTALL)
  include(Install)
endif ()
