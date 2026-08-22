include(FetchContent)

# CLI11
if (KUSAI_BUILD_APP)
  find_package(CLI11 CONFIG REQUIRED)
endif ()

# nlohmann json
find_package(nlohmann_json CONFIG QUIET)
if (NOT nlohmann_json_FOUND)
  FetchContent_Declare(nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
  )
  FetchContent_MakeAvailable(nlohmann_json)
endif()

# xxHash
cmake_pkg_config(IMPORT libxxhash QUIET)
if (TARGET PkgConfig::libxxhash)
  add_library(xxHash::xxhash ALIAS PkgConfig::libxxhash)
else()
  set(XXHASH_BUILD_XXHSUM OFF)
  FetchContent_Declare(
    xxhash
    GIT_REPOSITORY https://github.com/Cyan4973/xxHash.git
    GIT_TAG v0.8.3
    SOURCE_SUBDIR cmake_unofficial
  )
  FetchContent_MakeAvailable(xxhash)
endif()

# Pybind11
if (KUSAI_BUILD_PYTHON)
  find_package(pybind11 CONFIG REQUIRED)

  FetchContent_Declare(pybind11_json
    GIT_REPOSITORY https://github.com/pybind/pybind11_json.git
    GIT_TAG        master
    EXCLUDE_FROM_ALL
  )
  FetchContent_MakeAvailable(pybind11_json)
endif()

# Doxygen
if (KUSAI_BUILD_DOC)
  find_package(Doxygen REQUIRED COMPONENTS dot)
endif ()
