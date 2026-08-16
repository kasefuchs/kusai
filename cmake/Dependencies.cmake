include(FetchContent)

# CLI11
if (KUSAI_BUILD_APP)
  find_package(CLI11 CONFIG REQUIRED)
endif ()

# nlohmann json
find_package(nlohmann_json CONFIG REQUIRED)

# xxHash
cmake_pkg_config(IMPORT libxxhash REQUIRED)

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
