set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (APPLE)
  set(CMAKE_INSTALL_RPATH "@loader_path/../lib")
elseif (UNIX)
  set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
endif ()

set(CPACK_GENERATOR "TGZ")

include(CMakeDependentOption)
option(KUSAI_BUILD_APP "Build CLI app" OFF)
cmake_dependent_option(KUSAI_BUILD_SERVICE "Build grpc service" ON KUSAI_BUILD_APP OFF)
