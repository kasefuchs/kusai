cmake_minimum_required(VERSION 3.16)

project(kusai
  VERSION 0.2.0
  LANGUAGES CXX
)

include(CMakeDependentOption)
option(KUSAI_BUILD_APP "Build CLI app" OFF)
cmake_dependent_option(KUSAI_BUILD_SERVICE "Build grpc service" ON KUSAI_BUILD_APP OFF)

include(Settings.cmake)
include(Dependencies.cmake)

if (KUSAI_BUILD_APP)
    add_subdirectory(app)
endif ()

add_subdirectory(proto)
add_subdirectory(src)

include(Install.cmake)
